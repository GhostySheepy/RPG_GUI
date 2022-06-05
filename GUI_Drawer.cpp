#include "GUI_Drawer.h"

#include "WindowSlicer.h"

GUI_Drawer::GUI_Drawer(GUI_TextureHolder* new_TextureHolder)
{
	current_TextureHolder = new_TextureHolder;
}

void GUI_Drawer::MapToWindow(Window* draw_to, Map* map_to_draw, int centering_rad)
{
	sf::Vector2u sprite_size = current_TextureHolder->get_MapSprites()->getSpriteSizing();
	sf::Vector2u map_drawingCenter = { sprite_size.x * centering_rad, sprite_size.y * centering_rad };
	//sf::View map_view = draw_to->GetDefaultView();
	sf::View map_view = WindowSlicer::getMapWiev(draw_to);
	float scale_factor = 1/(map_view.getSize().x / ((centering_rad*2 + 1) * sprite_size.x));
	map_view.zoom(scale_factor);

	
	map_view.setCenter(static_cast<float>(map_drawingCenter.x + sprite_size.x / 2), static_cast<float>(map_drawingCenter.y + sprite_size.y / 2) );

	draw_to->SetView(map_view);

	using Helpers::normalize_int;
	int x_coord;
	int y_coord;

	std::pair<int, int> player_pos = map_to_draw->getPlayerPos();

	std::pair<int, int> from = { player_pos.first - centering_rad, player_pos.second - centering_rad };
	std::pair<int, int> to = { player_pos.first + centering_rad + 1, player_pos.second + centering_rad + 1 };

	std::pair<int, int> current_tile;
	sf::Vector2f current_drawing_pos;

	int current_type;

	sf::Sprite current_map_sprite;
	sf::Sprite current_player_sprite;
	sf::Sprite current_enemy_sprite;

	for (y_coord = from.second; y_coord < to.second; y_coord++)
	{
		for (x_coord = from.first; x_coord < to.first; x_coord++)
		{
			current_tile = Helpers::normalize_pair({ x_coord, y_coord }, map_to_draw->getSize());
			current_type = static_cast<int>(map_to_draw->checkTileForType(current_tile));
			current_map_sprite = current_TextureHolder->get_MapSprites()->getSpriteFor(current_type);
			current_drawing_pos = { x_coord * current_map_sprite.getGlobalBounds().width - from.first * current_map_sprite.getGlobalBounds().width, y_coord * current_map_sprite.getGlobalBounds().height - from.second * current_map_sprite.getGlobalBounds().height };
			current_map_sprite.setPosition(current_drawing_pos);

			draw_to->Draw(current_map_sprite);

			if (player_pos == current_tile) {
				current_player_sprite = current_TextureHolder->get_PlayerSprites()->getSpriteFor(0);
				current_player_sprite.setPosition(current_drawing_pos);
				draw_to->Draw(current_player_sprite);
			}

			if (map_to_draw->checkTileForEnemy(current_tile)) {
				current_enemy_sprite = current_TextureHolder->get_EnemySprites()->getSpriteFor(0);
				current_enemy_sprite.setPosition(current_drawing_pos);
				draw_to->Draw(current_enemy_sprite);
			}
		}
	}


}

void GUI_Drawer::InventoryToWindow(Window* draw_to)
{
	sf::View inv_view = WindowSlicer::getInventoryView(draw_to);
	draw_to->SetView(inv_view);
	sf::Vector2f inv_size = inv_view.getSize();

	sf::RectangleShape rect(inv_size);
	rect.setPosition(0, 0);
	rect.setFillColor(sf::Color(239, 245, 66));
	rect.setOutlineColor(sf::Color(124, 252, 0));
	rect.setOutlineThickness(-3);

	draw_to->Draw(rect);
}

void GUI_Drawer::CMDToWindow(Window* draw_to)
{
	sf::View cmd_view = WindowSlicer::getCMDView(draw_to);
	draw_to->SetView(cmd_view);
	sf::Vector2f cmd_size = cmd_view.getSize();

	sf::RectangleShape rect(cmd_size);
	rect.setPosition(0, 0);
	rect.setFillColor(sf::Color(239, 245, 66));
	rect.setOutlineColor(sf::Color(0, 254, 81));
	rect.setOutlineThickness(-3);

	draw_to->Draw(rect);
}

GUI_Drawer::~GUI_Drawer()
{
	delete current_TextureHolder;
}
