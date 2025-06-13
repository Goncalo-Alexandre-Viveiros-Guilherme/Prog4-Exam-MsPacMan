#include "MoveComponent.h"
#include "EngineTime.h"
#include "BoxColliderComponent.h"
#include "ServiceLocator.h"

MoveComponent::MoveComponent(dae::GameObject* parent, glm::vec2 gridSize)
    : Component(parent),
    m_Speed(5.f),
    m_CurrentDirection(DesiredDirection::None),
    m_DesiredDirection(DesiredDirection::None),
    m_GridSize(gridSize)
{
    m_CollisionComponent = GetParent()->GetComponent<CollisionComponent>();

    assert(m_CollisionComponent && "No Collision Component found");
}

void MoveComponent::Update()
{
    auto* parent = GetParent();
    auto pos = parent->GetWorldPosition();
    const bool nearIntersection = IsNearGridIntersection(pos);

    if (nearIntersection)
    {
        if (m_DesiredDirection != m_CurrentDirection && CanMove(m_DesiredDirection))
        {
            pos.x = std::round(pos.x / m_GridSize.x) * m_GridSize.x;
            pos.y = std::round(pos.y / m_GridSize.y) * m_GridSize.y;
            m_CurrentDirection = m_DesiredDirection;
        }
    }

    glm::vec3 move{};
    switch (m_CurrentDirection)
    {
    case DesiredDirection::Up:    move.y = -1; break;
    case DesiredDirection::Down:  move.y = 1;  break;
    case DesiredDirection::Left:  move.x = -1; break;
    case DesiredDirection::Right: move.x = 1;  break;
    default: break;
    }

    float delta = Time::GetInstance().GetDeltaTime();
    glm::vec3 newPos = pos + move * m_Speed * delta;

    if (!m_CollisionComponent->WouldCollide(newPos))
    {
        parent->SetLocalPosition(newPos.x, newPos.y);
    }
    else if (m_CurrentDirection != DesiredDirection::None)
    {
        m_CurrentDirection = DesiredDirection::None;

        glm::vec3 aligned{
            std::round(pos.x / m_GridSize.x) * m_GridSize.x,
            std::round(pos.y / m_GridSize.y) * m_GridSize.y,
            0
        };
        parent->SetLocalPosition(aligned.x, aligned.y);
    }
}

bool MoveComponent::CanMove(DesiredDirection direction)
{
    if (direction == DesiredDirection::None)
        return false;

    // Get current position and snap to grid for accurate check
    glm::vec3 currentPos = GetParent()->GetWorldPosition();
    glm::vec3 snappedPos = {
        std::round(currentPos.x / m_GridSize.x) * m_GridSize.x,
        std::round(currentPos.y / m_GridSize.y) * m_GridSize.y,
        0
    };

    // Calculate check position with a small tolerance
    const float tolerance = m_GridSize.x * 0.1f;
    glm::vec2 offset = GetDirectionOffset(direction);
    glm::vec3 checkPos = snappedPos + glm::vec3(offset * (m_GridSize - tolerance), 0);

    return !m_CollisionComponent->WouldCollide(checkPos);
}

glm::vec2 MoveComponent::GetDirectionOffset(DesiredDirection dir) const
{
    switch (dir)
    {
    case DesiredDirection::Up:    return { 0, -1 };
    case DesiredDirection::Down:  return { 0, 1 };
    case DesiredDirection::Left:  return { -1, 0 };
    case DesiredDirection::Right: return { 1, 0 };
    default: return { 0, 0 };
    }
}


bool MoveComponent::IsNearGridIntersection(const glm::vec3& pos) const
{
    float modX = std::fmod(pos.x, m_GridSize.x);
    float modY = std::fmod(pos.y, m_GridSize.y);

    if (modX < 0) modX += m_GridSize.x;
    if (modY < 0) modY += m_GridSize.y;

    const float leniency = 0.1f;
    return (modX < m_GridSize.x * leniency || modX > m_GridSize.x * (1 - leniency)) &&
        (modY < m_GridSize.y * leniency || modY > m_GridSize.y * (1 - leniency));
}


void MoveComponent::SetDesiredDirection(DesiredDirection desiredDirection)
{
    m_DesiredDirection = desiredDirection;

    if (m_CurrentDirection == DesiredDirection::None && CanMove(desiredDirection))
    {
        m_CurrentDirection = desiredDirection;
    }
}

void MoveComponent::SetSpeed(float speed)
{
    m_Speed = speed;
}