#include "GhostStates.h"

#include "GameObject.h"
#include "MoveComponent.h"

FSM::ChaseState::ChaseState(dae::GameObject* mainAgent)
{
	m_MoveComponent = mainAgent->GetComponent<MoveComponent>();

    m_MoveComponent->SetDesiredDirection(Left);

	m_MainAgent = mainAgent;

	assert(m_MoveComponent && "move component not found in main agent");
}

void FSM::ChaseState::OnEnter()
{
}

FSM::BlinkyChaseState::BlinkyChaseState(dae::GameObject* mainAgent, dae::GameObject* objectToChase): ChaseState(mainAgent)
{
	m_Target = objectToChase;
}

void FSM::BlinkyChaseState::Update()
{
    ChaseState::Update();

    const auto mainAgentPos = m_MainAgent->GetLocalPosition();
    const auto currentCellPosX = static_cast<int>(mainAgentPos.x) % (8 * 3);
    const auto currentCellPosY = static_cast<int>(mainAgentPos.y) % (8 * 3);

    if (currentCellPosX !=  m_LastCellPosX || currentCellPosY != m_LastCellPosY)
    {
        m_LastCellPosX = currentCellPosX;
        m_LastCellPosY = currentCellPosY;

        if (m_MoveComponent->IsNearGridIntersection(mainAgentPos))
        {
            const glm::vec2 targetPos = m_Target->GetLocalPosition();
            const glm::vec2 currentPos = m_MainAgent->GetLocalPosition();

            std::vector<DesiredDirection> possibleDirections;
            const DesiredDirection currentDir = m_MoveComponent->GetCurrentDirection();

            if (currentDir != Left) possibleDirections.push_back(Left);
            if (currentDir != Right) possibleDirections.push_back(Right);
            if (currentDir != Up) possibleDirections.push_back(Up);
            if (currentDir != Down) possibleDirections.push_back(Down);

            DesiredDirection bestDir = currentDir;
            float shortestDistance = FLT_MAX;

            for (DesiredDirection dir : possibleDirections) {
                if (m_MoveComponent->CanMove(dir)) {
                    glm::vec2 newPos = currentPos + m_MoveComponent->GetDirectionOffset(dir);
                    float distance = glm::distance(newPos, targetPos);

                    if (distance < shortestDistance) {
                        shortestDistance = distance;
                        bestDir = dir;
                    }
                }
            }

            if (bestDir != currentDir) {
                m_MoveComponent->SetDesiredDirection(bestDir);
            }
        }
    }
   
}