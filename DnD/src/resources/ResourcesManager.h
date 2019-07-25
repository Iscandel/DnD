#ifndef H__RESOURCESMANAGER__H
#define H__RESOURCESMANAGER__H

#include "IResource.h"
#include "tools/Singleton.h"
#include "tools/Timer.h"

#include <memory>
#include <mutex>
#include <map>

///////////////////////////////////////////////////////////////////////////////
///  \brief Abstract base class to handle game resources : images, sounds...
///  Template parameters : 
///  -T : Type of resource
///  -TypeId : Identier type of the resource (int, std::string...)
///  -singleton : it is the type of the derived class
///////////////////////////////////////////////////////////////////////////////
template<class T, class TypeId, class singleton>
class ResourcesManager : public Singleton<singleton>
{
public:
	typedef std::shared_ptr<T> PtrResource;
	typedef std::map<TypeId, PtrResource> MapResources;

	//RessourcesManager(void);
	//~RessourcesManager(void);

	///////////////////////////////////////////////////////////////////////////
	/// Returns the desired resource.
	/// 
	/// \param id Identifier of desired resource.
	///
	/// \return A smart pointer to the resource. Null pointer if it was not found
	///////////////////////////////////////////////////////////////////////////
	PtrResource getResource(TypeId id);

public:
	///////////////////////////////////////////////////////////////////////////
	/// Frees all current used resources if they are ONLY used by the Manager.
	///////////////////////////////////////////////////////////////////////////
	virtual void freeResources() = 0;

	///////////////////////////////////////////////////////////////////////////
	/// Frees the desired resources if it is ONLY used by the Manager (not used
	/// in the game for example).
	///
	/// \param id Identifier of the desired resource.
	///////////////////////////////////////////////////////////////////////////
	virtual void freeResource(TypeId id) = 0;

protected:
	///////////////////////////////////////////////////////////////////////////
	/// Searches and returns the desired resource if it is already present in 
	/// the manager. If the resource is not present, it returns a null pointer.
	///
	/// \param id Identifier of the desired resource.
	///
	/// \return A smart pointer to the resource, or a null pointer if it was 
	/// not found.
	///////////////////////////////////////////////////////////////////////////
	PtrResource findResource(TypeId id);

	///////////////////////////////////////////////////////////////////////////
	/// Loads the desired resource.
	///
	/// \param id Identifer of the desired resource.
	///
	/// \return A pointer to the resource.
	///////////////////////////////////////////////////////////////////////////
	virtual PtrResource loadResource(TypeId id) = 0;

protected:
	///Array containing all the resources, by identifier
	MapResources myResources;

};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
template<class T,class TypeId, class singleton>
typename ResourcesManager<T, TypeId, singleton>::PtrResource ResourcesManager<T, TypeId, singleton>::findResource(TypeId id)
{
	MapResources::iterator it = myResources.find(id);
	
	//Si la ressource n'a pas été trouvée, on renvoie  un pointeur nul
	if(it == myResources.end())
	{
		return PtrResource();
	}
	else
	{
		//Si la ressource existe et est chargée, on la renvoie
		if(it->second->getStatus() == IResource::IS_LOADED)
		{
			return it->second;
		}
		else if(it->second->getStatus() == IResource::NOT_LOADED)
		{
			//Si la ressource n'a pas encore été chargée, on renvoie un ptr nul
			return PtrResource();
		}
		else
		{
			//Si la ressource est en cours de chargement, on attend maximum 1.5s,
			//Au delà, on renvoie un pointeur nul
			Timer timer;

			while(it->second->getStatus() == IResource::IS_LOADING && timer.elapsedTime() < 1.5);

			if(timer.elapsedTime() < 1.5f)
				return it->second;
			else
				return PtrResource();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
template<class T,class TypeId, class singleton>
typename ResourcesManager<T, TypeId, singleton>::PtrResource ResourcesManager<T, TypeId, singleton>::getResource(TypeId id)
{
	//sf::Lock Lock(MonMutex);

	//On vérifie si la ressource existe
	PtrResource resultat = findResource(id);
	if(!resultat)
	{
		//Si la ressource n'existe pas ou n'est pas chargée, on s'en occupe
		resultat = loadResource(id);
		if(!resultat)
		{
			throw std::runtime_error("Resource not loaded. Id : " + id);
		}
	}

	return resultat;
}

#endif
