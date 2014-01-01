#include "BuildingDescription.h"

#include "GameEntity.h"
#include "RtsGame.h"
#include "GameType.h"
#include <cmath>
#include <cassert>

using namespace IStrategizer;

void BuildingDescription::InitializeAddressesAux()
{
	AddMemberAddress(2,
		&m_numberOfBuildings,
		&m_numberOfCriticalBuildings);
}
//----------------------------------------------------------------------------------------------
void BuildingDescription::AddEntity(GameEntity *p_entity)
{
	EntityClassType typeId;
	GameType		*pType;

	assert(p_entity);

	typeId = p_entity->Type();
	pType = g_Game->GetEntityType(typeId);
	assert(pType);

	if (pType->Attr(ECATTR_IsBuilding))
	{
		++m_numberOfBuildings;
		if (pType->Attr(ECATTR_IsCritical))
			++m_numberOfCriticalBuildings;
	}
}
//----------------------------------------------------------------------------------------------
void BuildingDescription::RemoveEntity(GameEntity *p_entity)
{
	EntityClassType typeId;
	GameType		*pType;

	assert(p_entity);

	typeId = p_entity->Type();
	pType = g_Game->GetEntityType(typeId);
	assert(pType);

	if (pType->Attr(ECATTR_IsBuilding))
	{
		--m_numberOfBuildings;

		if (pType->Attr(ECATTR_IsCritical))
			--m_numberOfCriticalBuildings;
	}
}
//----------------------------------------------------------------------------------------------
void BuildingDescription::Clear()
{
	m_numberOfBuildings = 0;
	m_numberOfCriticalBuildings = 0;
}
//----------------------------------------------------------------------------------------------
double BuildingDescription::GetDistance(BuildingDescription *p_other)
{
	double dist = 0.0;
	dist += abs(p_other->m_numberOfBuildings - m_numberOfBuildings);
	dist += abs(p_other->m_numberOfCriticalBuildings - m_numberOfCriticalBuildings);
	return dist;
}