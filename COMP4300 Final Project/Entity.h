#pragma once
#include "MemoryPool.h"

class Entity
{
	friend class EntityManager;

	size_t m_id{};

	// Private constructor that only EntityManager can access
	Entity(size_t id)
		: m_id{ id }
	{}

public:
	// Return the entity's id
	const size_t& getID() const
	{
		return m_id;
	}
	
	// Get the entity's tag through the memory pool
	const std::string& getTag() const
	{
		return MemoryPool::Instance().m_tags[m_id];
	}

	// Check if the entity is active through the memory pool
	const bool isActive() const
	{
		return MemoryPool::Instance().m_active[m_id];
	}

	// Get the entity's component through the memory pool
	template <typename Component>
	Component& getComponent()
	{
		return std::get<std::vector<Component>>(MemoryPool::Instance().m_pool)[m_id];
	}

	// Check if an entity has a component through the memory pool
	template <typename Component>
	bool hasComponent()
	{
		return std::get<std::vector<Component>>(MemoryPool::Instance().m_pool)[m_id].has;
	}

	// Add a component to the entity through the memory pool
	template <typename Component, typename... Targs>
	void addComponent(Targs&&... args)
	{
		std::get<std::vector<Component>>(MemoryPool::Instance().m_pool)[m_id] = Component{ std::forward<Targs>(args)... };
		std::get<std::vector<Component>>(MemoryPool::Instance().m_pool)[m_id].has = true;
	}

	// Remove an entity's component through the memory pool
	template <typename Component>
	void removeComponent()
	{
		std::get<std::vector<Component>>(MemoryPool::Instance().m_pool)[m_id].has = false;
	}

	// Destroy the entity through the memory pool
	const void destroy() const
	{
		MemoryPool::Instance().m_active[m_id] = false;
	}
};