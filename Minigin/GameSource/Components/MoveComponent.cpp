#include "MoveComponent.h"
#include "EngineTime.h"
#include "BoxColliderComponent.h"
#include "ServiceLocator.h"

MoveComponent::MoveComponent(dae::GameObject& parent, glm::vec2 gridSize)
    : Component(parent),
    m_Speed(5.f),
    m_CurrentDirection(DesiredDirection::None),
    m_DesiredDirection(DesiredDirection::None),
    m_GridSize(gridSize)
{
}

void MoveComponent::Update()
{
    auto* parent = GetParent();
    auto pos = parent->GetWorldPosition();
    const bool nearIntersection = IsNearGridIntersection(pos);

    // Handle direction changes
    if (nearIntersection || m_CurrentDirection == DesiredDirection::None)
    {
        // Always allow direction change if requested and possible
        if (m_DesiredDirection != m_CurrentDirection && CanMove(m_DesiredDirection))
        {
            // Snap to grid for clean movement
            if (nearIntersection)
            {
                pos.x = std::round(pos.x / m_GridSize.x) * m_GridSize.x;
                pos.y = std::round(pos.y / m_GridSize.y) * m_GridSize.y;
            }
            m_CurrentDirection = m_DesiredDirection;
        }
        // Stop if current direction is blocked
        else if (!CanMove(m_CurrentDirection))
        {
            m_CurrentDirection = DesiredDirection::None;
        }
    }

    // Calculate movement
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

    // Apply movement if valid
    if (!WouldCollide(newPos))
    {
        parent->SetLocalPosition(newPos.x, newPos.y);
    }
    else if (m_CurrentDirection != DesiredDirection::None)
    {
        // If colliding, stop movement
        m_CurrentDirection = DesiredDirection::None;

        // Try to align to grid to prevent getting stuck
        glm::vec3 alignedPos{
            std::round(pos.x / m_GridSize.x) * m_GridSize.x,
            std::round(pos.y / m_GridSize.y) * m_GridSize.y,
            0
        };
        if (!WouldCollide(alignedPos))
        {
            parent->SetLocalPosition(alignedPos.x, alignedPos.y);
        }
    }
}

bool MoveComponent::WouldCollide(const glm::vec3& position) const
{
    auto* collider = GetParent()->GetComponent<BoxColliderComponent>();
    if (!collider) return false;

    const glm::vec2 size = collider->GetSize();
    const float x = position.x;
    const float y = position.y;

    auto& collisionComponents = ServiceLocator::GetCollisionService().GetCollisionComponents();

    for (auto* other : collisionComponents)
    {
        if (other == collider || !other->GetIsBlocking()) continue;

        const glm::vec2 otherPos = other->GetLocalColliderPosition();
        const glm::vec2 otherSize = other->GetSize();

        // Simple AABB collision check
        if (x < otherPos.x + otherSize.x &&
            x + size.x > otherPos.x &&
            y < otherPos.y + otherSize.y &&
            y + size.y > otherPos.y)
        {
            return true;
        }
    }
    return false;
}

bool MoveComponent::IsNearGridIntersection(const glm::vec3& pos) const
{
    float modX = std::fmod(pos.x, m_GridSize.x);
    float modY = std::fmod(pos.y, m_GridSize.y);

    if (modX < 0) modX += m_GridSize.x;
    if (modY < 0) modY += m_GridSize.y;

    // Use 20% leniency
    const float leniency = 0.2f;
    return (modX < m_GridSize.x * leniency || modX > m_GridSize.x * (1 - leniency)) &&
        (modY < m_GridSize.y * leniency || modY > m_GridSize.y * (1 - leniency));
}

bool MoveComponent::CanMove(DesiredDirection direction)
{
    if (direction == DesiredDirection::None)
        return false;

    auto* collider = GetParent()->GetComponent<BoxColliderComponent>();
    if (!collider) return true;

    const glm::vec2 offset = GetDirectionOffset(direction);
    // Use 40% of grid size for checking ahead
    const float checkDistance = m_GridSize.x * 0.4f;

    // Check from the center of the collider
    glm::vec2 center = {
        collider->GetLocalColliderPosition().x + collider->GetSize().x / 2,
        collider->GetLocalColliderPosition().y + collider->GetSize().y / 2
    };

    glm::vec2 checkPos = center + offset * checkDistance;

    // Simple point collision check
    auto& collisionComponents = ServiceLocator::GetCollisionService().GetCollisionComponents();

    for (auto* other : collisionComponents)
    {
        if (other == collider || !other->GetIsBlocking()) continue;

        const glm::vec2 otherPos = other->GetLocalColliderPosition();
        const glm::vec2 otherSize = other->GetSize();

        if (checkPos.x >= otherPos.x &&
            checkPos.x <= otherPos.x + otherSize.x &&
            checkPos.y >= otherPos.y &&
            checkPos.y <= otherPos.y + otherSize.y)
        {
            return false;
        }
    }
    return true;
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

void MoveComponent::SetDesiredDirection(DesiredDirection desiredDirection)
{
    m_DesiredDirection = desiredDirection;
}

void MoveComponent::SetSpeed(float speed)
{
    m_Speed = speed;
}