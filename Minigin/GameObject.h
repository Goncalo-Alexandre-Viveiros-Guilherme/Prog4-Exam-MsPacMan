#pragma once
#include <string>
#include <memory>
#include <stdexcept>
#include <vector>
#include "Component.h"
#include "Transform.h"


namespace dae
{
	class GameObject final
	{
		
	public:
		void Update();
		void Render() const;

		void SetPosition(float x, float y);
		const glm::vec3& GetPosition() const;
		void SetToDestroy();
		bool GetIsMarkedForDestruction() const;
		std::vector<Component*> GetAllComponents();
		template <typename Comp>
		Comp& GetComponent() const
		{
			static_assert(std::is_base_of_v<Component, Comp>, "Template value must be a Component");

			for (Component* component : m_Components)
			{
				if (Comp* found = dynamic_cast<Comp*>(component)) 
				{
					return *found; 
				}
			}

			throw std::runtime_error("No component of that type found");
		}

        template <typename Comp, typename... Args>
        void AddComponent(Args&&... args)
        {
            static_assert(std::is_base_of_v<Component, Comp>, "Template value must be a Component");

            m_Components.push_back(new Comp(this, std::forward<Args>(args)...));
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
		void DeleteComponent(Component& componentToDelete);

		GameObject(std::string name);
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_Transform;
		bool m_IsEnabled;
		bool m_IsMarkedForDestruction{false};
		std::vector<Component*> m_Components;
		std::string m_Name;
	};

}
