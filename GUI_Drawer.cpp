#include "GUI_Drawer.h"

#include "WindowSlicer.h"

#include <Windows.h>

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

			if (map_to_draw->checkTileForEnemy(current_tile)) {
				current_enemy_sprite = current_TextureHolder->get_EnemySprites()->getSpriteFor(0);
				current_enemy_sprite.setPosition(current_drawing_pos);
				draw_to->Draw(current_enemy_sprite);
			}

			if (map_to_draw->checkTileForNPC(current_tile)) {
				current_enemy_sprite = current_TextureHolder->get_EnemySprites()->getSpriteFor(3);
				current_enemy_sprite.setPosition(current_drawing_pos);
				draw_to->Draw(current_enemy_sprite);
			}

			if (map_to_draw->checkTileForChest(current_tile)) {
				current_enemy_sprite = current_TextureHolder->get_ChestSprites()->getSpriteFor(0);
				current_enemy_sprite.setPosition(current_drawing_pos);
				draw_to->Draw(current_enemy_sprite);
			}

			if (player_pos == current_tile) {
				current_player_sprite = current_TextureHolder->get_PlayerSprites()->getSpriteFor(0);
				current_player_sprite.setPosition(current_drawing_pos);
				draw_to->Draw(current_player_sprite);
			}
		}
	}


}

void GUI_Drawer::InventoryToWindow(Window* draw_to, Player& current_player)
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

	sf::Font font = current_TextureHolder->get_CMDFontSheet()->getFont();

	//font.loadFromFile("electroharmonix.ttf");

	sf::Text inventory;

	inventory.setFont(font);

	inventory.setCharacterSize(20);

	inventory.setFillColor(sf::Color::Blue);

	inventory.setString("Inventory");

	inventory.setPosition(sf::Vector2f(3, 0));

	draw_to->Draw(inventory);
	//////////////////////////////////////////////

	int inv_view_capacity = 16;


	sf::RectangleShape item_empty(sf::Vector2f(39.f, 39.f));

	item_empty.setFillColor(rect.getFillColor());

	item_empty.setOutlineThickness(1.f);

	item_empty.setOutlineColor(sf::Color::Blue);

	sf::Vector2f item_shift = sf::Vector2f(46, 46), item_cords = sf::Vector2f(6, 40);


	for (int i = 0; i < current_player.getInventory().size(); i++)
	{
		Item current_item = current_player.getInventory()[i];

		//load texture of current_item
		
		sf::Sprite sprite = current_TextureHolder->get_ItemSprites()->getSpriteFor(current_item.getTextureIter());

		sprite.setScale(0.4, 0.4);

		sprite.setPosition(item_cords);



		draw_to->Draw(sprite);

		sf::Vector2i mouse_pos = sf::Mouse::getPosition(draw_to->getRenderWindow());

		if (mouse_pos.x > draw_to->getRenderWindow().getSize().x - rect.getSize().x + item_cords.x &&
			mouse_pos.x < draw_to->getRenderWindow().getSize().x - rect.getSize().x + item_cords.x + 40 &&
			mouse_pos.y > item_cords.y && mouse_pos.y < item_cords.y + 40 &&
			sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			current_player.equipItem(current_item, i);
			Sleep(100);
		}

		if (i == 3 || i == 7 || i == 11)
		{
			item_cords.y += item_shift.y;

			item_cords.x = 6;
		}
		else
		{
			item_cords.x += item_shift.x;
		}
	}

	for (int i = current_player.getInventory().size(); i < inv_view_capacity; i++)
	{
		item_empty.setPosition(item_cords);

		draw_to->Draw(item_empty);

		if (i == 3 || i == 7 || i == 11)
		{
			item_cords.y += item_shift.y;

			item_cords.x = 6;
		}
		else
		{
			item_cords.x += item_shift.x;
		}
	}
	//////////////////////////////////////////////
	sf::Sprite current_player_sprite = current_TextureHolder->get_PlayerSprites()->getSpriteFor(0);

	current_player_sprite.setPosition(sf::Vector2f(45, 250));

	current_player_sprite.setColor(sf::Color(255, 255, 255, 128));

	draw_to->Draw(current_player_sprite);


	inventory.setString("Equipment");

	inventory.setPosition(sf::Vector2f(3, 220));

	draw_to->Draw(inventory);


	item_empty.setFillColor(sf::Color(0, 0, 0, 0));

	item_empty.setSize(sf::Vector2f(25.f, 25.f));

	item_cords = sf::Vector2f(95, 250);

	if (current_player.isEquiped("Hat").getName() != "")
	{
		sf::Sprite hat_sprite = current_TextureHolder->get_ItemSprites()->getSpriteFor(current_player.isEquiped("Hat").getTextureIter());

		hat_sprite.setScale(0.25, 0.25);

		hat_sprite.setPosition(item_cords);

		draw_to->Draw(hat_sprite);

	}
	else
	{
		item_empty.setPosition(item_cords);

		draw_to->Draw(item_empty);
	}

	item_cords = sf::Vector2f(80, 280);

	if (current_player.isEquiped("Armor").getName() != "")
	{
		sf::Sprite armor_sprite = current_TextureHolder->get_ItemSprites()->getSpriteFor(current_player.isEquiped("Armor").getTextureIter());

		armor_sprite.setScale(0.25, 0.25);

		armor_sprite.setPosition(item_cords);

		draw_to->Draw(armor_sprite);
		
	}
	else
	{
		item_empty.setPosition(item_cords);

		draw_to->Draw(item_empty);
	}

	item_cords = sf::Vector2f(110, 295);

	if (current_player.isEquiped("Weapon").getName() != "")
	{
		sf::Sprite weapon_sprite = current_TextureHolder->get_ItemSprites()->getSpriteFor(current_player.isEquiped("Weapon").getTextureIter());

		weapon_sprite.setScale(0.25, 0.25);

		weapon_sprite.setPosition(item_cords);

		draw_to->Draw(weapon_sprite);

	}
	else
	{
		item_empty.setPosition(item_cords);

		draw_to->Draw(item_empty);
	}

	//////////////////////////////////////////////
	inventory.setString("    Stats");

	inventory.setPosition(sf::Vector2f(3, 350));

	draw_to->Draw(inventory);

	inventory.setCharacterSize(12);

	inventory.setFillColor(sf::Color::Black);

	std::string current_string;


	current_string = "Name: " + current_player.getName();

	inventory.setString(current_string);

	inventory.setPosition(sf::Vector2f(3, 400));

	draw_to->Draw(inventory);


	current_string = "Health: " + std::to_string(static_cast<int>(current_player.getHealth()));

	inventory.setString(current_string);

	inventory.setPosition(sf::Vector2f(3, 430));

	draw_to->Draw(inventory);


	current_string = "Damage: " + std::to_string(static_cast<int>(current_player.getDefaultDamage()));

	inventory.setString(current_string);

	inventory.setPosition(sf::Vector2f(3, 460));

	draw_to->Draw(inventory);


	current_string = "Money: " + std::to_string(current_player.getMoney());

	inventory.setString(current_string);

	inventory.setPosition(sf::Vector2f(3, 490));

	draw_to->Draw(inventory);


	current_string = "Experience: " + std::to_string(current_player.getExp());

	inventory.setString(current_string);

	inventory.setPosition(sf::Vector2f(3, 520));

	draw_to->Draw(inventory);
	//////////////////////////////////////////////
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

	sf::Font current_font = current_TextureHolder->get_CMDFontSheet()->getFont();

	sf::Text drawable_text;
	drawable_text.setFont(current_font);
	drawable_text.setString("d d d d d d d dddwwwwwwww");
	drawable_text.setCharacterSize(20);
	drawable_text.setFillColor(sf::Color(0, 0, 0));

	sf::FloatRect text_size = drawable_text.getLocalBounds();
	int font_size = 20 * ((cmd_size.x * 0.4) / text_size.width);

	text_size = drawable_text.getLocalBounds();

	drawable_text.setCharacterSize(font_size);


	int i_max;
	if (my_CMD_Stack.size() > 10) {
		i_max = 10;
	}
	else {
		i_max = my_CMD_Stack.size();
	}
	std::string overall_data = "\n";
	
	for (int i = 0; i < i_max; i++) {
		overall_data += my_CMD_Stack.at(i);
	}
	drawable_text.setString(overall_data);
	drawable_text.setPosition(0.5* text_size.height, (-0.5)*text_size.height);
	draw_to->Draw(drawable_text);

}

GUI_Drawer::~GUI_Drawer()
{
	delete current_TextureHolder;
}

void GUI_Drawer::CMD_PutToStack(std::string new_message)
{
	my_CMD_Stack.push_front(new_message);
}
