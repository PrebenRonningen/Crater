#pragma once

struct _TTF_Font;
namespace CraterEngine
{
	class Font
	{
	public:
		_TTF_Font* GetFont() const;
		explicit Font(const std::string& fullPath, unsigned int size);
		~Font();
	#pragma region deleted
		Font(const Font&) = delete;
		Font(Font&&) = delete;
		Font& operator= (const Font&) = delete;
		Font& operator= (const Font&&) = delete;
	#pragma endregion
	
	private:
		_TTF_Font* m_Font;
		unsigned int m_Size;
	};
}
