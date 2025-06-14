#include "GhostStates.h"

#include "EngineTime.h"
#include "Events.h"
#include "GameObject.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"


DesiredDirection GetReverseDirection(DesiredDirection dir)
{
    switch (dir) {
    case Up: return Down;
    case Down: return Up;
    case Left: return Right;
    case Right: return Left;
    default: return None;
    }
}

FSM::ChaseState::ChaseState(dae::GameObject* mainAgent, std::vector<glm::vec2> forbiddenCells):
m_ForbiddenCells(forbiddenCells)
{
	m_MoveComponent = mainAgent->GetComponent<MoveComponent>();

	m_MainAgent = mainAgent;

	assert(m_MoveComponent && "move component not found in main agent");
}

void FSM::ChaseState::OnEnter()
{
	if (const auto currentDir = m_MoveComponent->GetCurrentDirection(); currentDir == None)
    {
        m_MoveComponent->SetDesiredDirection(Left);
    }
    else
    {
        switch (currentDir)
        {
        case Up:
            m_MoveComponent->SetDesiredDirection(Down);
            break;
        case Down:
            m_MoveComponent->SetDesiredDirection(Up);
            break;
        case Left:
            m_MoveComponent->SetDesiredDirection(Right);
            break;
        case Right:
            m_MoveComponent->SetDesiredDirection(Left);
            break;
        }

    }
}

FSM::BlinkyChaseState::BlinkyChaseState(dae::GameObject* mainAgent, dae::GameObject* objectToChase, std::vector<glm::vec2> forbiddenCells): ChaseState(mainAgent, forbiddenCells)
{
	m_Target = objectToChase;
}

void FSM::BlinkyChaseState::OnEnter()
{
	ChaseState::OnEnter();
    m_MoveComponent->SetDesiredDirection(GetReverseDirection(m_MoveComponent->GetCurrentDirection()));
}

void FSM::BlinkyChaseState::Update()
{
    ChaseState::Update();

    const auto mainAgentPos = m_MainAgent->GetLocalPosition();
    const glm::vec2 gridSize = m_MoveComponent->GetGridSize();

    // Calculate current grid position
    const glm::ivec2 gridPos{
        static_cast<int>(std::round(mainAgentPos.x / gridSize.x)),
        static_cast<int>(std::round(mainAgentPos.y / gridSize.y))
    };

    // Check if current cell is forbidden
    bool isCurrentCellForbidden = false;
    for (const auto& forbiddenCell : m_ForbiddenCells) {
        if (glm::ivec2(forbiddenCell) == gridPos) {
            isCurrentCellForbidden = true;
            break;
        }
    }

    // If currently in a forbidden cell and moving down, force direction change
    if (isCurrentCellForbidden && m_MoveComponent->GetCurrentDirection() == Down) {
        m_MoveComponent->SetDesiredDirection(None); // Stop movement
        m_HasRecalculatedThisCell = false; // Allow immediate recalculation
    }

    // Only recalculate when entering a new grid cell
    if (gridPos != m_LastGridPos) {
        m_LastGridPos = gridPos;
        m_HasRecalculatedThisCell = false;
    }

    // Only make decisions at intersections and not already recalculated
    if (!m_HasRecalculatedThisCell &&
        m_MoveComponent->IsAtGridCenter(mainAgentPos) &&
        m_MoveComponent->IsNearGridIntersection(mainAgentPos))
    {
        m_HasRecalculatedThisCell = true;

        const glm::vec2 targetPos = m_Target->GetLocalPosition();
        const DesiredDirection currentDir = m_MoveComponent->GetCurrentDirection();

        std::vector<DesiredDirection> possibleDirections;

        // Get valid directions (can't reverse unless stuck)
        if (currentDir != Right && m_MoveComponent->CanMove(Left))
            possibleDirections.push_back(Left);
        if (currentDir != Left && m_MoveComponent->CanMove(Right))
            possibleDirections.push_back(Right);
        if (currentDir != Down && m_MoveComponent->CanMove(Up))
            possibleDirections.push_back(Up);

        // Only allow Down if not in forbidden cell
        if (currentDir != Up && m_MoveComponent->CanMove(Down) && !isCurrentCellForbidden)
            possibleDirections.push_back(Down);

        // If no valid directions, allow reverse as last resort
        if (possibleDirections.empty() && currentDir != None) {
            if (m_MoveComponent->CanMove(GetReverseDirection(currentDir))) {
                possibleDirections.push_back(GetReverseDirection(currentDir));
            }
        }

        // Choose best direction
        if (!possibleDirections.empty()) {
            DesiredDirection bestDir = currentDir;
            float minDistance = FLT_MAX;

            for (DesiredDirection dir : possibleDirections) {
                glm::vec2 newPos = glm::vec2(mainAgentPos) + m_MoveComponent->GetDirectionOffset(dir) * gridSize;
                float distance = glm::distance(newPos, targetPos);

                if (distance < minDistance) {
                    minDistance = distance;
                    bestDir = dir;
                }
            }

            if (bestDir != currentDir) {
                m_MoveComponent->SetDesiredDirection(bestDir);
            }
        }
    }
}


FSM::BlinkyFrightenedState::BlinkyFrightenedState(dae::GameObject* mainAgent, glm::vec2 targetPos)
{
    m_MoveComponent = mainAgent->GetComponent<MoveComponent>();

    m_MainAgent = mainAgent;

    m_Target = targetPos;

    assert(m_MoveComponent && "move component not found in main agent");
}

void FSM::BlinkyFrightenedState::OnEnter()
{
    m_MoveComponent->SetDesiredDirection(GetReverseDirection(m_MoveComponent->GetCurrentDirection()));
    m_MainAgent->GetComponent<SpriteComponent>()->SetTexture("DizzyGhost.png");
}

void FSM::BlinkyFrightenedState::Update()
{

    const glm::vec2 gridSize = m_MoveComponent->GetGridSize();
    const auto mainAgentPos = m_MainAgent->GetLocalPosition();

    const glm::ivec2 gridPos{
        static_cast<int>(std::round(mainAgentPos.x / gridSize.x)),
        static_cast<int>(std::round(mainAgentPos.y / gridSize.y))
    };

    // Only recalculate when entering a new grid cell
    if (gridPos != m_LastGridPos)
    {
        m_LastGridPos = gridPos;
        m_HasRecalculatedThisCell = false;
    }

    if (!m_HasRecalculatedThisCell &&
        m_MoveComponent->IsAtGridCenter(mainAgentPos) &&
        m_MoveComponent->IsNearGridIntersection(mainAgentPos))
    {
        m_HasRecalculatedThisCell = true;

        const DesiredDirection currentDir = m_MoveComponent->GetCurrentDirection();

        std::vector<DesiredDirection> possibleDirections;


        if (currentDir != Right && m_MoveComponent->CanMove(Left))
            possibleDirections.push_back(Left);
        if (currentDir != Left && m_MoveComponent->CanMove(Right))
            possibleDirections.push_back(Right);
        if (currentDir != Down && m_MoveComponent->CanMove(Up))
            possibleDirections.push_back(Up);
        if (currentDir != Up && m_MoveComponent->CanMove(Down))
            possibleDirections.push_back(Down);

        if (possibleDirections.empty() && currentDir != None) {
            if (m_MoveComponent->CanMove(GetReverseDirection(currentDir))) {
                possibleDirections.push_back(GetReverseDirection(currentDir));
            }
        }

        DesiredDirection bestDir = currentDir;
        float minDistance = FLT_MAX;

        for (DesiredDirection dir : possibleDirections) {
            glm::vec2 newPos = glm::vec2(mainAgentPos) + m_MoveComponent->GetDirectionOffset(dir);
            float distance = glm::distance(newPos, m_Target);

            if (distance < minDistance) {
                minDistance = distance;
                bestDir = dir;
            }
        }

        if (bestDir != currentDir) {
            m_MoveComponent->SetDesiredDirection(bestDir);
        }
    }
}

void FSM::BlinkyFrightenedState::OnExit()
{
    m_MainAgent->GetComponent<SpriteComponent>()->SetTexture("Blinky.png");
}

FSM::HasPowerPelletBeenEaten::HasPowerPelletBeenEaten()
{
    EventDispatcher::GetInstance().AddListener<EdibleGhostsEvent>
        (nullptr, [this](EdibleGhostsEvent event)
            {
                SetHasPowerPelletBeenEaten(true);
                event;
            }
        );
}

bool FSM::HasPowerPelletBeenEaten::Evaluate()
{
	if (m_HasPowerPelletBeenEaten)
	{
        m_HasPowerPelletBeenEaten = false;
		return true;
	}
    return false;
}

void FSM::HasPowerPelletBeenEaten::SetHasPowerPelletBeenEaten(bool value)
{
    m_HasPowerPelletBeenEaten = value;
}

FSM::TimerIsWeak::TimerIsWeak() = default;

bool FSM::TimerIsWeak::Evaluate() 
{
	if (m_HowLongHasBeenWeak > 4)
	{
        m_HowLongHasBeenWeak = 0;
        return true;
	}

	m_HowLongHasBeenWeak += Time::GetInstance().GetDeltaTime();

	return false;
}
