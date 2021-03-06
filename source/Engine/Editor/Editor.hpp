#pragma once
#include "UI/UIUtil.hpp"
#include "Singleton.hpp"

#ifdef EDITOR

class TextureData;
class EditorRenderer;

class Editor : public Singleton<Editor>
{
public:

	void Initialize();

	void Update();
	void Draw();

	GLuint GetSceneTarget();

	void OnWindowResize(ivec2 EditorDimensions);
	void CalculateViewportSize(ivec2 FullWindowDimensions);

	const iRect& GetViewport() const { return m_Viewport; }

	//std::vector<UISprite> GetSprites() { return m_UISprites; }

private:

	EditorRenderer* m_pRenderer = nullptr;

	bool m_RedrawUI = true;

	float m_ToolbarSeparator = 200;
	iRect m_Viewport;
	
	//std::vector<UISprite> m_UISprites;

private:
	//Disable constructors
	friend class Singleton<Editor>;

	Editor();
	virtual ~Editor();

	Editor( const Editor& t );
	Editor& operator=( const Editor& t );
};

#endif