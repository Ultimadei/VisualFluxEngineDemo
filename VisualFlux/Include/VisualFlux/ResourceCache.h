#pragma once

#include <string>
#include <map>

namespace VisualFlux {
	template<typename _CacheType, typename _KeyType = std::string>
	class ResourceCache {
	public:
		ResourceCache() {}
		~ResourceCache() {}

		/*
			-- VFEngine::ResourceCache<typename _CacheType, typename _KeyType>::getCachedResource --
			Is a function which returns a value from the cache map.
			If the value is not found in the map, an error is thrown
			-- Arguments --
			- key : The key for the map to use in order to look up the cached resource 
		*/
		const _CacheType getCachedResource(_KeyType key);

		/*
			-- Overload --
			Looks up a cached resource. If it does not exist, then it adds it to the map.
			Then returns the found or created value
			- key : The key for the map to use in order to find or add the given value
			- value : The resource to cache if nothing is found under key
		*/
		const _CacheType getCachedResource(_KeyType key, _CacheType value);

		/*
		-- VFEngine::ResourceCache<typename _CacheType, typename _KeyType>::addResource --
		Is a function which adds a given value to the map, under key
		If the value already exists, 
		-- Arguments --
		- key : The key for the map to use in order to add the given value
		- value : The resource to cache
		- replace : Whether or not the given value should replace a pre-existing one
		*/
		void addResource(_KeyType key, _CacheType value, bool replace);
	private:
		std::map <_KeyType, _CacheType> _cacheMap;
	};

	template<typename _CacheType, typename _KeyType>
	inline const _CacheType ResourceCache<_CacheType, _KeyType>::getCachedResource(_KeyType key) {

		const auto iterator = _cacheMap.find(key);


		if (iterator == _cacheMap.end()) {
			// The value was not found under the key. Throw an error
			std::ostringstream ss;
			ss << "Could not locate a value under the given key\n";
			throw new std::runtime_error(ss.str());
		}
		else {
			// The value was found, so return it.
			return iterator->second;
		}
	}

	template<typename _CacheType, typename _KeyType>
	inline const _CacheType ResourceCache<_CacheType, _KeyType>::getCachedResource(_KeyType key, _CacheType value) {
		const auto iterator = _cacheMap.find(key);


		if (iterator == _cacheMap.end()) {
			// The value was not found under the key. Add it to the map
			_cacheMap.emplace(key, value);
			return value;
		}
		else {
			// The value was found, so return it.
			return iterator->second;
		}
	}

	template<typename _CacheType, typename _KeyType>
	inline void ResourceCache<_CacheType, _KeyType>::addResource(_KeyType key, _CacheType value, bool replace) {
		const auto iterator = _cacheMap.find(key);

		if (iterator == _cacheMap.end()) {
			// There was no value under the key, so we add it
			_cacheMap.emplace(key, value);
		}
		else {
			if (replace) {
				// There was a value found, but we are allowed to replace it
				iterator->second = value;
			}
			else {
				// There was a value found, but we are not allowed to replace it. So return.
				return;
			}
		}
	}
}