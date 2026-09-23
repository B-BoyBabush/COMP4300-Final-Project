#pragma once

#include "Entity.h"
#include "MemoryPool.h"
#include "Components.h"

#include <vector>
#include <tuple>

class EntityManager
{
	std::vector<Entity> m_entities{};
	std::vector<Entity> m_toAdd{};

public:
	EntityManager()
	{}

	std::vector<Entity>& getEntities()
	{
		return m_entities;
	}

	// Get all components of that type through the memory pool
	template <typename Component>
	std::vector<Component>& getComponent()
	{
		return std::get<std::vector<Component>>(MemoryPool::Instance().m_pool);
	}

	// Add an entity
	Entity addEntity(const std::string& tag)
	{
		size_t id{ 0 };
		bool noMemory{ true };
		
		// Scan for an inactive entity id
		for (size_t i{ 0 }; i < MemoryPool::Instance().m_active.size(); i++){
			if (MemoryPool::Instance().m_active[i] == false)
			{
				id = i;
				noMemory = false;
				MemoryPool::Instance().m_active[id] = true;
				break;
			}
		}

		// If the memory pool does not have space for the entity, resize it
		if (noMemory)
		{
			// Set the id to one above the current number of entities
			id = MemoryPool::Instance().numEntities + 1;

			// Double the size of the memory pool
			MemoryPool::Instance().numEntities *= 2;
			MemoryPool::Instance().resize(MemoryPool::Instance().numEntities);
		}
		
		Entity entity{ id };
		MemoryPool::Instance().m_tags[id] = tag;

		// Reset all components
		std::get<std::vector<CTransform>>(MemoryPool::Instance().m_pool)[entity.m_id] = CTransform{};
		std::get<std::vector<CBoundingBox>>(MemoryPool::Instance().m_pool)[entity.m_id] = CBoundingBox{};
		std::get<std::vector<CAnimation>>(MemoryPool::Instance().m_pool)[entity.m_id] = CAnimation{};
		std::get<std::vector<CDraggable>>(MemoryPool::Instance().m_pool)[entity.m_id] = CDraggable{};
		
		// Add entity to add queue
		m_toAdd.push_back(entity);
		return entity;
	}
	
	// Update entity manager
	void update()
	{
		// Move entities from add queue to entity container
		for (Entity entity : m_toAdd)
		{ m_entities.push_back(entity); }

		// Clear add queue
		m_toAdd.clear();
	}
};