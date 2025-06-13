#include "GhostStates.h"

#include "GameObject.h"
#include "MoveComponent.h"

FSM::ChaseState::ChaseState(dae::GameObject* mainAgent)
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

FSM::BlinkyChaseState::BlinkyChaseState(dae::GameObject* mainAgent, dae::GameObject* objectToChase): ChaseState(mainAgent)
{
	m_Target = objectToChase;
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

    // Only recalculate when entering a new grid cell
    if (gridPos != m_LastGridPos)
    {
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
        if (currentDir != Up && m_MoveComponent->CanMove(Down))
            possibleDirections.push_back(Down);

        // If no valid directions, allow reverse as last resort
        if (possibleDirections.empty() && currentDir != None) {
            if (m_MoveComponent->CanMove(GetReverseDirection(currentDir))) {
                possibleDirections.push_back(GetReverseDirection(currentDir));
            }
        }

        DesiredDirection bestDir = currentDir;
        float minDistance = FLT_MAX;

        for (DesiredDirection dir : possibleDirections) {
            glm::vec2 newPos = glm::vec2 (mainAgentPos) + m_MoveComponent->GetDirectionOffset(dir);
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

DesiredDirection FSM::BlinkyChaseState::GetReverseDirection(DesiredDirection dir) {
    switch (dir) {
    case Up: return Down;
    case Down: return Up;
    case Left: return Right;
    case Right: return Left;
    default: return None;
    }
}