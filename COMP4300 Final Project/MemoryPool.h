#pragma once

#include "Components.h"

#include <tuple>
#include <vector>
#include <string>
#include <iostream>

class MemoryPool
{
	friend class Entity;
	friend class EntityManager;
	
	typedef std::tuple<
		std::vector<CTransform>,
		std::vector<CBoundingBox>
	> ComponentVectorTuple;

private:
	size_t						numEntities{};
	ComponentVectorTuple		m_pool{};
	std::vector<std::string>	m_tags{};
	std::vector<bool>			m_active{};

	MemoryPool(size_t maxEntities)
		: numEntities{ maxEntities }
	{
		// Reserve space
		std::get<std::vector<CTransform>>(m_pool).reserve(numEntities);
		std::get<std::vector<CBoundingBox>>(m_pool).reserve(numEntities);

		m_tags.reserve(numEntities);
		m_active.reserve(numEntities);
		
		// Set size and set to default initializations
		std::get<std::vector<CTransform>>(m_pool).resize(numEntities);
		std::get<std::vector<CBoundingBox>>(m_pool).resize(numEntities);

		m_tags.resize(numEntities);
		m_active.resize(numEntities);
	}

	void resize(const size_t& size)
	{
		numEntities = size;

		// Reserve new space
		std::get<std::vector<CTransform>>(m_pool).reserve(numEntities);
		std::get<std::vector<CBoundingBox>>(m_pool).reserve(numEntities);

		m_tags.reserve(numEntities);
		m_active.reserve(numEntities);

		// Resize
		std::get<std::vector<CTransform>>(m_pool).resize(numEntities);
		std::get<std::vector<CBoundingBox>>(m_pool).resize(numEntities);

		m_tags.resize(numEntities);
		m_active.resize(numEntities);
	}

	// Only one memory pool can be created
	// Only accessible through Entity and EntityManager functions
	static MemoryPool& Instance()
	{
		static MemoryPool memoryPool{ 400 }; // ??? Use macro to get specific amount
		return memoryPool;
	}

public:
	// Check the size of all variables
	void print()
	{
		std::cout << "Container m_tags has a capacity of " << m_tags.capacity() << " and a size of " << m_tags.size() << '\n';
		std::cout << "Container m_active has a capacity of " << m_active.capacity() << " and a size of " << m_active.size() << '\n';

		size_t data{ sizeof(m_pool) + numEntities * (sizeof(CTransform) + sizeof(CBoundingBox)) };
		std::cout << "Container m_pool has a size of " << data << '\n';
		std::cout << "Container CTransform has a capacity of " << std::get<std::vector<CTransform>>(m_pool).capacity() << " and a size of " << std::get<std::vector<CTransform>>(m_pool).size() << '\n';
		std::cout << "Container CBoundingBox has a capacity of " << std::get<std::vector<CBoundingBox>>(m_pool).capacity() << " and a size of " << std::get<std::vector<CBoundingBox>>(m_pool).size() << '\n';
	}
};