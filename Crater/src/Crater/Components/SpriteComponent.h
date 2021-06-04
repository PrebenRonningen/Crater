#pragma once
#include "Crater/Components/Component.h"
#include "Crater/Objects/Texture2D.h"
#include "Crater/Components/RenderableComponent.h"

namespace CraterEngine
{
	class GameObject;
	struct TextureData;
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

		void SetTexture(const std::string& filePath);
		virtual bool Initialize() override;
		virtual void Update(const float ) override{};
		void SetTextureSource(int row, int col);
		void GetRowAndCol(int& row, int& col)const{
			float column = float(m_TextureInfo.sourceRectange.x) / m_TextureInfo.textureRect.w;
			float rw = float(m_TextureInfo.sourceRectange.y) / m_TextureInfo.textureRect.h;

			col = int(column * m_Columns);
			row = int(rw * m_Rows);
		}
	private:
		//void UpdateTextureInfo(const int srcRow = 0, const int srcCol = 0);
		void PassTextureToRenderComponent();

		void FillTextureData();

		Texture2D* m_pTexture2D;
		std::string m_TexturePath;
		RenderableComponent* m_pParentRenderComponent;
		TextureData m_TextureInfo;
		int m_Rows;
		int m_Columns;
	};
}