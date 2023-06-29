#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
namespace mt
{
	struct Point_c { float x, y; };
	class Column
	{
	private:
		sf::Texture* m_texture;			//Текстура
		sf::Sprite* m_column = nullptr;	//Спрайт
		float m_scale;                  //Масштаб
		float m_Rx;						//Радиус - x
		float m_Ry;						//Радиус - y
		Point_c m_p_c0;					//Точка

	public:
		Column() {}													//Конструктор

		bool Column::Setup_Column_Top(float scale, Point_c p0)
		{
			m_texture = new sf::Texture();
			if (!m_texture->loadFromFile("assets//column.png"))
			{std::cout << "Error" << std::endl; return false;}
			m_column = new sf::Sprite;
			m_column->setTexture(*m_texture);
			float x = m_texture->getSize().x;
			float y = m_texture->getSize().y;
			m_scale = scale;
			m_column->setScale(m_scale, m_scale);
			m_column->setOrigin(x / 2, y / 2);
			m_Ry = m_texture->getSize().y * m_scale / 2;
			m_Rx = m_texture->getSize().x * m_scale / 2;

			m_column->setRotation(180.f);
			m_p_c0.x = p0.x + 2 * m_Rx;
			m_p_c0.y = p0.y;
			m_column->setPosition(m_p_c0.x, m_p_c0.y);

			return true;
		}

		bool Column::Setup_Column_Bottom(float scale, Point_c p0)
		{
			m_texture = new sf::Texture();
			if (!m_texture->loadFromFile("assets//column.png"))
			{
				std::cout << "Error" << std::endl; return false;
			}
			m_column = new sf::Sprite;
			m_column->setTexture(*m_texture);
			float x = m_texture->getSize().x;
			float y = m_texture->getSize().y;
			m_scale = scale;
			m_column->setScale(m_scale, m_scale);
			m_column->setOrigin(x / 2, y / 2);
			m_Ry = m_texture->getSize().y * m_scale / 2;
			m_Rx = m_texture->getSize().x * m_scale / 2;

			m_p_c0.x = p0.x + 2 * m_Rx;
			m_p_c0.y = p0.y;
			m_column->setPosition(m_p_c0.x, m_p_c0.y);

			return true;
		}

		sf::Sprite* Get() { return m_column; }
		
		void Columns_move(double deltaTime) {
			m_p_c0.x -= 100 * deltaTime;
			m_column->setPosition(m_p_c0.x, m_p_c0.y);
		}

		void Random_Shift_Top(float m_Height, int m_random_number, float m_R) {
				m_p_c0.y = m_Height - m_random_number - 2 * m_Ry - 20 - 2*m_R;
		}

		void Random_Shift_Bottom(float m_Height, int m_random_number) {
			m_p_c0.y = m_Height - m_random_number;
		}
		
		void Restart(float m_Width) {
			m_p_c0.x = m_Width+m_Width/4;
		}
		void Restart_2(float m_Width, int i) {
			m_p_c0.x = m_Width + i * m_Width / 4;
		}
		Point_c GetPosition_c() {
			Point_c x {m_column->getPosition().x, m_p_c0.y}; //Получение текущей позиции центра объекта
			return x;
		}
		float RadiusY_c() { return m_Ry; }					 //Получение радиуса - y 
		float RadiusX_c() { return m_Rx; }                   //Получение радиуса - x
	};
}