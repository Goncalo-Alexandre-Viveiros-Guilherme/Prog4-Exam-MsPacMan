#include "MoveComponent.h"

#include "EngineTime.h"
#include "EventDispatcher.h"
#include "Events.h"
#include "GameObject.h"
#include "BoxColliderComponent.h"
#include "SDL_rect.h"
#include "ServiceLocator.h"

MoveComponent::MoveComponent(dae::GameObject& parent,glm::vec2 gridSize)
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

    // Store previous position for collision recovery
    glm::vec3 previousPos = pos;

    // Only allow direction changes when near intersections
    if (nearIntersection)
    {
        // Try desired direction first
        if (m_DesiredDirection != m_CurrentDirection && CanMove(m_DesiredDirection))
        {
            // Snap to grid for clean movement
            pos.x = std::round(pos.x / m_GridSize.x) * m_GridSize.x;
            pos.y = std::round(pos.y / m_GridSize.y) * m_GridSize.y;
            m_CurrentDirection = m_DesiredDirection;
        }
        // If current direction is blocked, stop
        else if (!CanMove(m_CurrentDirection))
        {
            m_CurrentDirection = DesiredDirection::None;
        }
    }

    // Apply movement
    glm::vec3 move{};
    switch (m_CurrentDirection)
    {
    case DesiredDirection::Up:    move.y -= 1; break;
    case DesiredDirection::Down:  move.y += 1; break;
    case DesiredDirection::Left:  move.x -= 1; break;
    case DesiredDirection::Right: move.x += 1; break;
    default: break;
    }

    float delta = Time::GetInstance().GetDeltaTime();
    pos += move * m_Speed * delta;

    // Check if new position would collide
    if (WouldCollide(pos))
    {
        // If colliding, nudge back slightly instead of full stop
        pos = previousPos;

        // For more precise collision response:
        // Try moving only in X or Y axis separately
        glm::vec3 tryX = previousPos;
        tryX.x += move.x * m_Speed * delta;
        if (!WouldCollide(tryX)) pos.x = tryX.x;

        glm::vec3 tryY = previousPos;
        tryY.y += move.y * m_Speed * delta;
        if (!WouldCollide(tryY)) pos.y = tryY.y;

        // If completely blocked, stop movement
        if (WouldCollide(pos))
        {
            m_CurrentDirection = DesiredDirection::None;
        }
    }

    parent->SetLocalPosition(pos.x, pos.y);
}

bool MoveComponent::WouldCollide(const glm::vec3& position) const
{
    auto* collider = GetParent()->GetComponent<BoxColliderComponent>();
    if (!collider) return false;

    // Check collision at the given position
    SDL_FRect futureBounds{
        position.x,
        position.y,
        collider->GetSize().x,
        collider->GetSize().y
    };

    auto& collisionComponents = ServiceLocator::GetCollisionService().GetCollisionComponents();
    auto& collisionShapes = ServiceLocator::GetCollisionService().GetCollisionShapes();

    for (int idx = 0; idx < collisionComponents.size(); idx++)
    {
        if (collisionComponents[idx] == collider) continue;

        const glm::vec2 otherPos = collisionComponents[idx]->GetLocalColliderPosition();
        const auto* shape = collisionShapes[idx];
        const glm::vec2 size = shape->GetDescriptor().box.size;

        if (collisionComponents[idx]->GetIsBlocking() &&
            IsCollidingAABB(futureBounds.x, futureBounds.y,
                otherPos.x, otherPos.y,
                size.x, size.y))
        {
            return true;
        }
    }
    return false;
}

bool MoveComponent::IsCollidingAABB(float ax, float ay, float bx, float by, float bw, float bh) const
{
    return (ax < bx + bw) &&
        (ax + m_GridSize.x > bx) &&
        (ay < by + bh) &&
        (ay + m_GridSize.y > by);
}

bool MoveComponent::IsNearGridIntersection(const glm::vec3& pos) const
{
    float modX = std::fmod(pos.x, m_GridSize.x);
    float modY = std::fmod(pos.y, m_GridSize.y);

    if (modX < 0) modX += m_GridSize.x;
    if (modY < 0) modY += m_GridSize.y;

    // More lenient threshold (try adjusting these values)
    const float leniencyX = m_GridSize.x * 0.3f; // 30% of cell size
    const float leniencyY = m_GridSize.y * 0.3f;

    return (modX < leniencyX || modX >(m_GridSize.x - leniencyX)) &&
        (modY < leniencyY || modY >(m_GridSize.y - leniencyY));
}


bool MoveComponent::CanMove(DesiredDirection direction)
{
    if (direction == DesiredDirection::None)
        return false;

    auto* collider = GetParent()->GetComponent<BoxColliderComponent>();
    if (!collider)
        return true;

    const glm::vec2 offset = GetDirectionOffset(direction);
    // Check just a small distance ahead (half grid size or less)
    const float checkDistance = std::min(m_GridSize.x, m_GridSize.y) * 0.5f;

    return !collider->IsCollidingInDirection(offset, checkDistance);
}

glm::vec2 MoveComponent::GetDirectionOffset(DesiredDirection dir) const
{
    switch (dir)
    {
    case DesiredDirection::Up: return { 0, -1 };
    case DesiredDirection::Down: return { 0, 1 };
    case DesiredDirection::Left: return { -1, 0 };
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
