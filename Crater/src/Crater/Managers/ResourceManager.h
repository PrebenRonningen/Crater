#pragma once
#include "Singleton.h"

namespace CraterEngine
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		Texture2D* LoadTexture(const std::string& file) const;
		Font* LoadFont(const std::string& file, unsigned int size) const;
		void SetNewDataPath(const std::string& dataPath){m_DataPath = dataPath;};
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_DataPath;
	};
}
