#include <Game.hpp>
#include <Bird.hpp>
#include <Obstacle.hpp>
#include <thread>
#include <chrono>
#include <SFML/Audio.hpp>
#include <string>

namespace mt
{
	void Game::Setup(int m_Width, int m_Height, const std::string& m_caption) {			//Создание окна
		m_window = new sf::RenderWindow(sf::VideoMode(m_Width, m_Height), m_caption);	//Окно с заданными параметрами
		m_window->setFramerateLimit(60);}												//Ограничение FPS
	
	//Основная функция 
	void Game::Run(float m_Width, float m_Height) {

		//FPS//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		int fps = 0;																	//				
		int fps_count = 0;																//		
		sf::Font font; font.loadFromFile("assets//font_1.ttf");							//Шрифт	 FPS
		sf::Text fps_text; fps_text.setFont(font); fps_text.setCharacterSize(20);		//Шрифт	
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		//Счёт/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		int score = 0;
		int best_score = 0;
		sf::Font font_score; font_score.loadFromFile("assets//font_1.ttf");
		sf::Text score_text; score_text.setFont(font_score); score_text.setCharacterSize(20);
		score_text.setPosition(0,20);
		sf::Text best_score_text; best_score_text.setFont(font_score); best_score_text.setCharacterSize(20);
		best_score_text.setPosition(0, 40);
		sf::Font font_score_in_the_end; font_score_in_the_end.loadFromFile("assets//font_2.otf");
		sf::Text score_text_in_the_end; score_text_in_the_end.setFont(font_score_in_the_end); score_text_in_the_end.setCharacterSize(50);
		score_text_in_the_end.setPosition(m_Width/6, m_Height/8);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Стартовая надпись
		sf::Text start_text; start_text.setFont(font_score); start_text.setCharacterSize(30);

		//Создание птицы///////////////////////////////////////////////////////////////////////////////////////////////////
		mt::Bird* Bird = new mt::Bird();												//Сам объект
		Bird->Setup(0.25);																//Его параметры через функцию
		Bird->Spawn({ 200,252 });														//Начальное расположение 
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		//Колонны//////////////////////////////////////////////////////////////////////////////////////////////////////////
		std::vector<mt::Column*> Columns;												//Вектор с колоннами
		mt::Column* Column1 = new mt::Column();
		Column1->Setup_Column_Top				(0.25,{m_Width,10});
		Columns.push_back(Column1);

		mt::Column* Column2 = new mt::Column();
		Column2->Setup_Column_Bottom			(0.25,{m_Width,m_Height-10});
		Columns.push_back(Column2);

		mt::Column* Column3 = new mt::Column();
		Column3->Setup_Column_Top				(0.25,{m_Width+m_Width/4,10});
		Columns.push_back(Column3);

		mt::Column* Column4 = new mt::Column();
		Column4->Setup_Column_Bottom			(0.25,{m_Width+m_Width/4,m_Height-10});
		Columns.push_back(Column4);

		mt::Column* Column5 = new mt::Column();
		Column5->Setup_Column_Top				(0.25,{m_Width+2*m_Width/4,10});
		Columns.push_back(Column5);

		mt::Column* Column6 = new mt::Column();
		Column6->Setup_Column_Bottom			(0.25,{m_Width+2*m_Width/4,m_Height-10});
		Columns.push_back(Column6);

		mt::Column* Column7 = new mt::Column();
		Column7->Setup_Column_Top				(0.25,{m_Width+3*m_Width/4,10});
		Columns.push_back(Column7);

		mt::Column* Column8 = new mt::Column();
		Column8->Setup_Column_Bottom			(0.25,{m_Width+3*m_Width/4,m_Height-10});
		Columns.push_back(Column8);

		mt::Column* Column9 = new mt::Column();
		Column9->Setup_Column_Top				(0.25,{m_Width+4*m_Width/4,10});
		Columns.push_back(Column9);

		mt::Column* Column10 = new mt::Column();
		Column10->Setup_Column_Bottom			(0.25,{m_Width+4*m_Width/4,m_Height-10});
		Columns.push_back(Column10);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//Фон//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////			
		sf::Texture background_texture;	background_texture.loadFromFile("assets//background.png");
		sf::Sprite background; background.setTexture(background_texture);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//Основной Цикл////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool bird_is_alive = true;
		bool start = false;
		m_timer.restart();
		while (m_window->isOpen()) 
		{	
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {start=true;m_timer.restart();} //Старт
			if (start){
				//FPS - подсчёты///////////////////////////////////////////////////////////////////////////////////////////////////
				sf::Time elapsed = timer_fps.getElapsedTime();								//Таймер прошедшего времени
				if (elapsed.asMilliseconds() >= 1000)										//Если прошла секунда, то 
				{																			//
					fps = fps_count;														//fps=fps_count 
					fps_count = 0;															//обнуляем счётчик
					timer_fps.restart();													//обнуляем таймер
				}
				fps_text.setString("FPS: " + std::to_string(fps));;							//Преобразовываем значения в строку
				fps_count++;																//Прибавляем счётчик
				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//Цикл обработки событий системы///////////////////////////////////////////////////////////////////////////////////
				sf::Event event;
				while (m_window->pollEvent(event)) if (event.type == sf::Event::Closed) m_window->close();
				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				if (bird_is_alive) {
					bool bird_up_or_down = false;
					//ПТИЦА////////////////////////////////////////////////////////////////////////////////////////////////////////
					Point p = Bird->GetPosition();
					float Bird_Ry = Bird->RadiusY(); float Bird_Rx = Bird->RadiusX();

					sf::Time deltaTime = m_timer.restart();											//Получаем время выполнения цикла

					if (p.y - Bird_Ry > 0)//Вверх
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
							Bird->UP(deltaTime.asSeconds());bird_up_or_down = true;}

					if (p.y + Bird_Ry <= m_Height)//Вниз
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
							Bird->DOWN(deltaTime.asSeconds()); bird_up_or_down = true;}

					if(!bird_up_or_down) Bird->Zero_rotation();
					////////////////////////////////////////////////////////////////////////////////////////////////////////////////

					//КОЛОННЫ///////////////////////////////////////////////////////////////////////////////////////////////////////
					int Random_Height = rand() % 100;												//Рандомные числа

					for (int i = 0; i < Columns.size(); i += 2) {									//Движение колонн
						Point_c p_c = Columns[i]->GetPosition_c();									//Центр каждой нижней колонны
						float R_c_x = Columns[i]->RadiusX_c();										//Ширина от центра до края 
						if (m_Width <= p_c.x - R_c_x) {												//Пока колонна за правым краем экрана
							Columns[i]->Random_Shift_Top(m_Height, Random_Height, Bird_Ry);			//Рандомные положения колонн
							Columns[i + 1]->Random_Shift_Bottom(m_Height, Random_Height);			//	
						}
						if (0 >= p_c.x + R_c_x) {													//Респаун колонн после ухода за левый край
							Columns[i]->Restart(m_Width);											//
							Columns[i + 1]->Restart(m_Width);										//

						}
						Columns[i]->Columns_move(deltaTime.asSeconds());							//Движение верхней колонны
						Columns[i + 1]->Columns_move(deltaTime.asSeconds());						//Движение нижней колонны
						float R_c_y = Columns[i]->RadiusY_c();
						if (p_c.x - R_c_x <= p.x + Bird_Rx) { 										//Взаимодействие с колоннами по Ox
							if (p_c.x + R_c_x >= p.x + Bird_Rx) {									//
								if (p_c.y + R_c_y >= p.y - Bird_Ry) {								//Взаимодействие птицы и верхней колонны по Oy
									bird_is_alive = false;
								}
								if (p_c.y + R_c_y + 20 + 2 * Bird_Ry <= p.y + Bird_Ry) {			//Взаимодействие птицы и нижней колонны по Oy
									bird_is_alive = false;
								}
							}
							else if (p_c.x + R_c_x <= p.x - Bird_Rx)
								if (p_c.x + R_c_x + 95*deltaTime.asSeconds() >= p.x - Bird_Rx)
									score += 1;
						}
						score_text.setString("SCORE: " + std::to_string(score));
						if (score > best_score) best_score = score;
						best_score_text.setString("BEST SCORE: " + std::to_string(best_score));
						score_text_in_the_end.setString("YOUR SCORE: " + std::to_string(score) + "\n" + "BEST SCORE: " +std::to_string(best_score));
					}
				}
			}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				m_window->clear();																//Очистка перед отрисовыванием
				//Отрисовка////////////////////////////////////////////////////////////////////////////////////////////////////
				m_window->draw(background);														//Вывод фона

				if (!start) { 																	//Стартовый текст
					start_text.setPosition(80, 152);
					start_text.setString("PRESS SPACE TO START");
					m_window->draw(start_text);
				}
				if (bird_is_alive) {															//Пока птица жива
					for (int i = 0; i < Columns.size(); i++)									//Вывод колонн
						m_window->draw(*Columns[i]->Get());										//
					m_window->draw(*Bird->Get());												//Вывод птицы
					m_window->draw(fps_text);													//Вывод FPS
					m_window->draw(score_text);													//Вывод счёта
					m_window->draw(best_score_text);
				}
				if (!bird_is_alive) {															//Финальный счёт
					m_window->draw(score_text_in_the_end);
					start_text.setPosition(m_Width / 2.5 , m_Height / 8 + 100);
					start_text.setString("PRESS R TO RESPAWN");
					m_window->draw(start_text);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {							//Респаун колонн
						for (int i = 0; i < 1; i++) {
							Columns[i]->Restart_2(m_Width, i);
							Columns[i+1]->Restart_2(m_Width, i);
						}
						for (int i = 2; i < 3; i++) {
							Columns[i]->Restart_2(m_Width, i-1);
							Columns[i+1]->Restart_2(m_Width, i-1);
						}
						for (int i = 4; i < 5; i++) {
							Columns[i]->Restart_2(m_Width, i-2);
							Columns[i + 1]->Restart_2(m_Width, i-2);
						}
						for (int i = 6; i < 7; i++) {
							Columns[i]->Restart_2(m_Width, i - 3);
							Columns[i + 1]->Restart_2(m_Width, i - 3);
						}
						for (int i = 8; i < 9; i++) {
							Columns[i]->Restart_2(m_Width, i - 4);
							Columns[i + 1]->Restart_2(m_Width, i - 4);
						}
						score = 0;
						Bird->Spawn({ 200,252 });
						bird_is_alive = true;
						m_timer.restart();
						}
					}
				//Отображение
				m_window->display();															
		}
		//Удаление элементов для очистки памяти 
		delete Bird;
		for (int i = 0; i < Columns.size(); i++)
			delete Columns[i];
	};
}