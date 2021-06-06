#pragma once
#include "Crater/Components/Component.h"
#include "Crater/Objects/Texture2D.h"
#include "Crater/Components/RenderableComponent.h"

namespace CraterEngine
{
	class GameObject;
	
	class SpriteComponent final : public Component
	{
	public:
		SpriteComponent(const GameObject* parent, const std::string& filePath = "", const int rows = 1, const int columns = 1);
		virtual ~SpriteComponent();

#pragma region deleted
		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;
#pragma endregion

		virtual bool Initialize() override;
		virtual void Update( const float ) override{
			UpdateDestination();
		};
		virtual void Render() const override;

		void SetTexture(const std::string& filePath);
		void SetTextureSource(int row, int col);
		void UpdateDestination();
		void SetDestination(int x, int y);
		void GetRowAndCol(int& row, int& col) const;
		const TextureData& GetTexInfo()
		{
			FillTextureData(); 
			return m_TextureInfo;
		};
	private:

		void FillTextureData();

		Texture2D* m_pTexture2D;
		std::string m_TexturePath;
		TextureData m_TextureInfo;
		int m_Rows;
		int m_Columns;
	};
}