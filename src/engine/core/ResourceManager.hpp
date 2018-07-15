#ifndef __ENGINE_CORE_RESOURCE_MANAGER_H__
#define	__ENGINE_CORE_RESOURCE_MANAGER_H__

#include <functional>
#include <string>
#include <SFML/Graphics.hpp>
#include "ResourceContainer.hpp"

namespace Engine
{
	namespace Core
	{
		class ResourceManager
		{
		public:
			typedef ResourceContainer<int, sf::Shader> ShaderContainer;
			typedef ResourceContainer<int, sf::Texture> TextureContainer;
			typedef ResourceContainer<int, sf::Font> FontContainer;

			enum ResourceType
			{
				Shader,
				Texture,
				Font
			};

			typedef function<void(const ResourceType type, const int resourceId, const std::string& fileName)> LoadCallback;

		public:
			ResourceManager();

			ShaderContainer* getShaderContainer();
			TextureContainer* getTextureContainer();
			FontContainer* getFontContainer();

			void loadAll();
			void loadAll(LoadCallback callback);
			void clearAll();

		private:			
			ShaderContainer shaderContainer; 		
			TextureContainer textureContainer;
			FontContainer fontContainer;	
		};
	}
}

#endif