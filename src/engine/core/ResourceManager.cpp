#include "ResourceManager.hpp"

namespace Engine
{
	namespace Core
	{
		ResourceManager::ResourceManager() :
			shaderContainer(),
			textureContainer(),
			fontContainer()
		{
		}

		ResourceManager::ShaderContainer* ResourceManager::getShaderContainer()
		{
			return &shaderContainer;
		}

		ResourceManager::TextureContainer* ResourceManager::getTextureContainer()
		{
			return &textureContainer;
		}

		ResourceManager::FontContainer* ResourceManager::getFontContainer()
		{
			return &fontContainer;
		}

		void ResourceManager::loadAll()
		{
			shaderContainer.loadAll();
			textureContainer.loadAll();
			fontContainer.loadAll();
		}

		void ResourceManager::loadAll(ResourceManager::LoadCallback callback)
		{
			shaderContainer.setLoadCallback([callback](int resourceId, const std::string& fileName) { callback(ResourceManager::ResourceType::Shader, resourceId, fileName); });
			textureContainer.setLoadCallback([callback](int resourceId, const std::string& fileName) { callback(ResourceManager::ResourceType::Texture, resourceId, fileName); });
			fontContainer.setLoadCallback([callback](int resourceId, const std::string& fileName) { callback(ResourceManager::ResourceType::Font, resourceId, fileName); });
			
			shaderContainer.loadAll();
			textureContainer.loadAll();
			fontContainer.loadAll();
		}

		void ResourceManager::clearAll()
		{
			shaderContainer.clear();
			textureContainer.clear();
			fontContainer.clear();
		}
	}
}