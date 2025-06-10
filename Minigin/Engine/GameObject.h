#pragma once
#include <string>
#include <memory>
#include <stdexcept>
#include <vector>
#include "Transform.h"
#include "Engine/Components/Component.h"

class Observer;

namespace dae
{
	class GameObject final
	{
		
	public:
		void Update();
		void FixedUpdate() const;
		void Render() const;

		void SetLocalPosition(float x, float y);
		void SetLocalPosition(const glm::vec3& pos);
		const glm::vec3& GetLocalPosition() const;
		void UpdateWorldPosition();
		const glm::vec3& GetWorldPosition();
		void SetToDestroy();
		bool GetIsMarkedForDestruction() const;
		std::vector<Component*> GetAllComponents();

		template <typename Comp>
		Comp* GetComponent() const
		{
			static_assert(std::is_base_of_v<Component, Comp>, "Template value must be a Component");

			for (Component* component : m_Components)
			{
				if (Comp* found = dynamic_cast<Comp*>(component)) 
				{
					return found; 
				}
			}

			throw std::runtime_error("No component of that type found");
		}
        template <typename Comp, typename... Args>
        void AddComponent(Args&&... args)
        {
            static_assert(std::is_base_of_v<Component, Comp>, "Template value must be a Component");

            m_Components.push_back(new Comp(*this, std::forward<Args>(args)...));
        }
		template <typename Comp>
		bool HasComponent() const
		{
			static_assert(std::is_base_of_v<Component, Comp>, "Template value must be a Component");

			for (Component* component : m_Components)
			{
				if (Comp* found = dynamic_cast<Comp*>(component))
				{
					return true;
				}
			}

			return false;
		}
		template <typename Comp>
		void RemoveComponent() const
		{
			static_assert(std::is_base_of_v<Component, Comp>, "Template value must be a Component");

			if (HasComponent<Comp>())
			{
				GetComponent<Comp>().SetToDestroy();
			}
			else
			{
				throw std::runtime_error("No component of that type found");
			}
		}

		std::string GetName();
		void DeleteComponent(const Component& componentToDelete);
		void SetParent(GameObject* parent,bool keepWorldPosition);
		bool HasParent() const;
		std::vector<GameObject*>& GetGameObjectChildren();

		GameObject(const std::string& name);
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;


	private:
		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);
		bool IsChild(GameObject* child) const;
		void SetPositionDirty();

		Transform m_Transform;
		bool m_IsEnabled;
		bool m_IsPositionDirty{ false };
		bool m_IsMarkedForDestruction{false};
		std::vector<Component*> m_Components;
		std::vector<GameObject*> m_Children;
		GameObject* m_Parent;
		std::string m_Name;
	};

}
