#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
namespace mt
{
	struct Point {float x, y;};	  //Точка
	class Bird
	{
	private:
		sf::Texture* m_texture;			//Текстура
		sf::Sprite* m_bird = nullptr;	//Спрайт
		float m_scale;                  //Масштаб
		float m_Rx;						//Радиус - x
		float m_Ry;						//Радиус - y
		Point m_p0;						//Точка

	public:
		Bird() {}													//Конструктор

		bool Bird::Setup(float scale)
		{
			m_texture = new sf::Texture();							//Создание текстуры птицы
			if (!m_texture->loadFromFile("assets//bird.png"))		//
			{std::cout << "Error" << std::endl;return false;}		//
			m_bird = new sf::Sprite;								//Создание спрайта
			m_bird->setTexture(*m_texture);							//Установка текстуры для спрайта
			float x = m_texture->getSize().x;
			float y = m_texture->getSize().y;
			m_scale = scale;
			m_bird->setScale(m_scale, m_scale);						//Изменение размера объекта	
			m_bird->setOrigin(x / 2, y / 2);						//Смещение системы координат объекта в его центр
			m_Ry = m_texture->getSize().y * m_scale / 4;
			m_Rx = m_texture->getSize().x * m_scale / 4;

			return true;
		}
		sf::Sprite* Get() {return m_bird;}

		void Spawn(Point p0) {
			m_p0 = p0;
			m_bird->setPosition(m_p0.x, m_p0.y);					//Установка начальной позиции спрайта
		}

		void DOWN(double deltaTime) {
			m_bird->setRotation(45.f);

			m_p0.y += 150*deltaTime;
			m_bird->setPosition(m_p0.x, m_p0.y);
;		}

		void UP(double deltaTime) {
			m_bird->setRotation(-45.f);								//Поворот на 45 градусов вверх при взлёте

			m_p0.y -= 150 * deltaTime;					
			m_bird->setPosition(m_p0.x,m_p0.y );					//Меняем положение спрайта по y

		}

		void Zero_rotation() {m_bird->setRotation(0.f);}

		Point GetPosition() {
			Point y{m_p0.x, m_bird->getPosition().y};					//Получение текущей позиции центра объекта
			return y;
		}		
		float RadiusY() {return m_Ry;}								   //Получение радиуса - y 
		float RadiusX() {return m_Rx;}                                 //Получение радиуса - x
	};
}