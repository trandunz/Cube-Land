//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CMainMenu.cpp
// Description : CMainMenu Implementation file.
// Author : William Inman
// Mail : william.inman@mds.ac.nz
//


#include "CMainMenu.h"

/// <summary>
/// CMainMenu Constructor
/// </summary>
/// <param name="_renderWindow"></param>
/// <param name="_font"></param>
CMainMenu::CMainMenu(sf::RenderWindow* _renderWindow, sf::Font& _font, std::string _bgPath)
{
    m_RenderWindow = _renderWindow;
    m_Font = &_font;
    Start(_bgPath);
}

/// <summary>
/// CMainMenu Destructor
/// </summary>
CMainMenu::~CMainMenu()
{
    DeletePointer(m_Play);
    DeletePointer(m_Options);
    DeletePointer(m_Exit);
    m_Play = nullptr;
    m_Options = nullptr;
    m_Exit = nullptr;
    m_Font = nullptr;
    m_RenderWindow = nullptr;
}

/// <summary>
/// CMainMenu Start
/// </summary>
void CMainMenu::Start(std::string _bgPath)
{
    CreateBackGroundImage(_bgPath);
    CreateTitle();
    CreateButtons();
}

/// <summary>
/// CMainMenu Update
/// </summary>
/// <param name="_event"></param>
void CMainMenu::Update()
{
    if (!m_bClose)
    {
        m_MousePos = m_RenderWindow->mapPixelToCoords(sf::Mouse::getPosition(*m_RenderWindow));
        RainbowTitle();
        ParralaxBackground();
        ButtonUpdates();
    }
    else if (m_bClose)
    {
        m_RenderWindow->close();
    }
}

void CMainMenu::PolledUpdate(sf::Event& _event)
{
    while (m_RenderWindow->pollEvent(_event))
    {
        if (_event.type == sf::Event::Closed)
        {
            m_RenderWindow->close();
        }
    }
}

/// <summary>
/// Inherited draw Function 
/// Note: Use m_Renderwindow->draw(CMainMenu);
/// </summary>
/// <param name="_target"></param>
/// <param name="_states"></param>
void CMainMenu::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
    // apply the transform
    _states.transform *= getTransform();

    // our particles don't use a texture
    _states.texture = &m_MainMenuTexture;

    // draw the vertex array
    _target.draw(m_MainMenuImage, _states);
    _target.draw(m_Title, _states);
    _target.draw(m_Credit, _states);
    RenderButtons(_target, _states);
}

/// <summary>
/// Creates the background image
/// </summary>
void CMainMenu::CreateBackGroundImage(std::string _bgPath)
{
    LoadSpriteTexture(LoadTexture(&m_MainMenuTexture, _bgPath), &m_MainMenuImage);
    m_MainMenuImage.setPosition(m_RenderWindow->getView().getCenter());
    m_MainMenuImage.setScale(1.1f, 1.1f);
    m_MainMenuImage.setTextureRect(sf::IntRect(0, 0, m_MainMenuImage.getTexture()->getSize().x * 1000, m_MainMenuImage.getTexture()->getSize().y));
}

/// <summary>
/// Creates the title "Planetary"
/// </summary>
void CMainMenu::CreateTitle()
{
    m_TitleString = "Planetary";
    m_Title.setFont(*m_Font);
    m_Title.setCharacterSize(256);
    m_Title.setString(m_TitleString);
    m_Title.setOrigin(m_Title.getGlobalBounds().width / 2, m_Title.getGlobalBounds().height / 2);
    m_Title.setFillColor(sf::Color::Magenta);
    m_Title.setOutlineColor(sf::Color::Black);
    m_Title.setOutlineThickness(3);
    m_Title.setPosition(m_RenderWindow->getView().getCenter().x, m_RenderWindow->getView().getCenter().y - m_RenderWindow->getSize().y / 2.5);

    m_Credit.setFont(*m_Font);
    m_Credit.setCharacterSize(28);
    m_Credit.setString("Created By: William Inman");
    m_Credit.setOrigin(m_Credit.getGlobalBounds().width / 2, m_Credit.getGlobalBounds().height / 2);
    m_Credit.setFillColor(sf::Color(51,102,255));
    m_Credit.setOutlineColor(sf::Color::Black);
    m_Credit.setOutlineThickness(3);
    m_Credit.setPosition(m_RenderWindow->getView().getCenter().x, m_RenderWindow->getView().getCenter().y - m_RenderWindow->getSize().y / 4);

}

/// <summary>
/// Updates the title with a rainbow effect
/// </summary>
void CMainMenu::RainbowTitle()
{
    if (m_RainbowClock.getElapsedTime().asSeconds() >= 0.5f)
    {
        m_Title.setFillColor(sf::Color(rand() % 256, rand() % (256 - rand() % 256), rand() % 255 - (rand() % 256) - (rand() % (256 - rand() % 256),255)));
        m_Title.setOutlineColor(sf::Color::Black);

        m_RainbowClock.restart();
    }
}

/// <summary>
/// Main Menu Parralax Background effect
/// </summary>
void CMainMenu::ParralaxBackground()
{
    if (m_ParralaxClock.getElapsedTime().asSeconds() >= 0.03f)
    {
        if (m_MainMenuImage.getPosition().x <= m_MainMenuImage.getTextureRect().width / 2)
        {
            m_MainMenuImage.setPosition(m_MainMenuImage.getPosition().x - 1, m_MainMenuImage.getPosition().y);
        }
        else
        {
            m_MainMenuImage.setPosition(m_MainMenuImage.getPosition().x + m_MainMenuImage.getTextureRect().width, m_MainMenuImage.getPosition().y);
        }

        m_ParralaxClock.restart();
    }
    
}

/// <summary>
/// Creates all buttons
/// </summary>
void CMainMenu::CreateButtons()
{
    m_Play = new CButtons(m_RenderWindow);
    m_Play->SetFontSize(256);
    m_Play->SetLabel("Play");
    m_Play->SetPosition(m_RenderWindow->getView().getCenter().x, m_RenderWindow->getView().getCenter().y - m_Play->Sprite.getGlobalBounds().width * 4);
    m_Play->SetSpritePos(m_RenderWindow->getView().getCenter().x - 80, m_RenderWindow->getView().getCenter().y + 30 - m_Play->Sprite.getGlobalBounds().width * 4);
    m_Play->m_tLabel.setOutlineThickness(3);

    m_Options = new CButtons(m_RenderWindow);
    m_Options->SetFontSize(256);
    m_Options->SetLabel("Options");
    m_Options->SetPosition(m_RenderWindow->getView().getCenter().x, m_RenderWindow->getView().getCenter().y + m_Options->Sprite.getGlobalBounds().width * 0);
    m_Options->SetSpritePos(m_RenderWindow->getView().getCenter().x - 80, m_RenderWindow->getView().getCenter().y + 30 + m_Options->Sprite.getGlobalBounds().width * 0);
    m_Options->m_tLabel.setOutlineThickness(3);

    m_Exit = new CButtons(m_RenderWindow);
    m_Exit->SetFontSize(256);
    m_Exit->SetLabel("Exit");
    m_Exit->SetPosition(m_RenderWindow->getView().getCenter().x, m_RenderWindow->getView().getCenter().y + m_Exit->Sprite.getGlobalBounds().width * 4);
    m_Exit->SetSpritePos(m_RenderWindow->getView().getCenter().x - 80, m_RenderWindow->getView().getCenter().y + 30 + m_Exit->Sprite.getGlobalBounds().width * 4);
    m_Exit->m_tLabel.setOutlineThickness(3);
}

/// <summary>
/// Updates all buttons
/// </summary>
void CMainMenu::ButtonUpdates()
{
    m_Play->Update();
    m_Options->Update();
    m_Exit->Update();

    if (m_ButtonTimer.getElapsedTime().asSeconds() < 0.3f)
    {
        if (m_Play->bIsinBounds(m_MousePos) && IsMouseLeftPressed())
        {
            InterceptSceneChange(1);
        }
        else if (m_Exit->bIsinBounds(m_MousePos) && IsMouseLeftPressed())
        {
            m_RenderWindow->close();
        }

        m_ButtonTimer.restart();
    }
}

/// <summary>
/// Renders all buttons
/// </summary>
/// <param name="_target"></param>
/// <param name="_states"></param>
void CMainMenu::RenderButtons(sf::RenderTarget& _target, sf::RenderStates _states) const
{
    _target.draw(m_Play->m_tLabel, _states);
    _target.draw(m_Options->m_tLabel, _states);
    _target.draw(m_Exit->m_tLabel, _states);

    _target.draw(m_Play->Sprite, _states);
    _target.draw(m_Options->Sprite, _states);
    _target.draw(m_Exit->Sprite, _states);
}

/// <summary>
/// Initializes the button textures
/// </summary>
/// <param name="_texture1"></param>
/// <param name="_texture2"></param>
void CMainMenu::InitButtonTextures(std::string _texture1, std::string _texture2)
{
    m_MainMenuButtonTexture_Hover.loadFromFile(_texture1);
    m_MainMenuTexture.loadFromFile(_texture2);
}

bool CMainMenu::IsMouseLeftPressed()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        return true;
    }
    else
    {
        return false;
    }
}
