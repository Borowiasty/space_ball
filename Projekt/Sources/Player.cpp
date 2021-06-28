#include "../Headers/Player.h"

Player_part::Player_part(const std::map<std::string, sf::Texture>& textures, int index, double pos_x, double pos_y) : Sprite()
{
    index_ = index;
    setTexture(textures.at("pad"));
    switch (index_)
    {
    case 0:
        setTextureRect(sf::IntRect(0, 0, 10, getGlobalBounds().height));
        break;
    case 1:
        setTextureRect(sf::IntRect(13, 0, 33, getGlobalBounds().height));
        break;
    case 2:
        setTextureRect(sf::IntRect(13, 0, 60, getGlobalBounds().height));
        break;
    case 3:
        setTextureRect(sf::IntRect(13, 0, 33, getGlobalBounds().height));
        break;
    case 4:
        setTextureRect(sf::IntRect(getGlobalBounds().width - 10, 0, 10, getGlobalBounds().height));
        break;
    }
    setScale({ 1.5,1.5 });
    setPosition(sf::Vector2f(pos_x, pos_y));
}

std::tuple<double, double> Player_part::bounce(double speed_x, double speed_y, int shoud_be) const
{
    switch (index_)
    {
    case 0:
        if (speed_x > 0) { return std::make_tuple<double, double>(speed_x * -1.5, speed_y * -0.5); }
        else { return std::make_tuple<double, double>(speed_x * 1.5, -0.5); }
        break;
    case 1:
        if (speed_x > 0) { return std::make_tuple<double, double>(speed_x * -1.2, speed_y * -0.8); }
        else { return std::make_tuple<double, double>(speed_x * 1.1, speed_y * -0.9); }
        break;
    case 2:
        if (abs(speed_x) < abs(speed_y)) { return std::make_tuple<double, double>(((shoud_be * 1.0) - 10) * (speed_x / abs(speed_x)), shoud_be + 10 * (-1.0)); }
        else if (abs(speed_x) > abs(speed_y)) { return std::make_tuple<double, double>(((shoud_be * 1.0) + 10) * (speed_x / abs(speed_x)), shoud_be - 10 * (-1.0)); }
        else { return std::make_tuple<double, double>((shoud_be * 1.0) * (speed_x / abs(speed_x)), shoud_be * (-1.0)); }
        break;
    case 3:
        if (speed_x > 0) { return std::make_tuple<double, double>(speed_x * 1.2, speed_y * -0.8); }
        else { return std::make_tuple<double, double>(speed_x * -1.1, speed_y * -0.9); }
        break;
    case 4:
        if (speed_x > 0) { return std::make_tuple<double, double>(speed_x * 1.5, speed_y * -0.5); }
        else { return std::make_tuple<double, double>(speed_x * -1.5, speed_y * -0.5); }
        break;
    default:
        return std::make_tuple<double, double>(speed_x * 1.0, speed_y * 1.0);
    }
}

Player::Player(const std::map<std::string, sf::Texture>& textures, double pos_x, double pos_y)
{
    pad_.emplace_back(textures, 0, pos_x, pos_y);
    pad_.emplace_back(textures, 1, pad_[pad_.size() - 1].getGlobalBounds().left + pad_[pad_.size() - 1].getGlobalBounds().width, pad_[pad_.size() - 1].getGlobalBounds().top);
    pad_.emplace_back(textures, 2, pad_[pad_.size() - 1].getGlobalBounds().left + pad_[pad_.size() - 1].getGlobalBounds().width, pad_[pad_.size() - 1].getGlobalBounds().top);
    pad_.emplace_back(textures, 3, pad_[pad_.size() - 1].getGlobalBounds().left + pad_[pad_.size() - 1].getGlobalBounds().width, pad_[pad_.size() - 1].getGlobalBounds().top);
    pad_.emplace_back(textures, 4, pad_[pad_.size() - 1].getGlobalBounds().left + pad_[pad_.size() - 1].getGlobalBounds().width, pad_[pad_.size() - 1].getGlobalBounds().top);
}

const Player_part& Player::pad(int index) { return pad_[index]; }

int Player::pad_size() { return pad_.size(); }

void Player::step(sf::Time time, const sf::Window& window)
{
    if (changing_size_[0])
    {
        changing_size_[1] -= time.asSeconds();
        if (changing_size_[1] <= 0.0)
        {
            changing_size_[1] = 0.0;

            if (changing_size_[0] == 1) { make_it_smaller(); }
            else { make_it_bigger(); }
            changing_size_[0] = 0;
        }
    }
    if (speed_[1] != 0.0)
    {
        speed_[1] -= time.asSeconds();

        if (speed_[1] <= 0.0) { make_it_slower(); }
    }
    if (stop_[1] != 0.0)
    {
        stop_[1] -= time.asSeconds();

        if (stop_[1] <= 0.0) { make_it_move(); }
    }

    if (stop_[0] == 0.0)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if (pad_[pad_.size() - 1].getGlobalBounds().left + pad_[pad_.size() - 1].getGlobalBounds().width < window.getSize().x)
            {
                for (auto& pad_part : pad_)
                {
                    pad_part.move(speed_[0] * time.asSeconds(), 0);
                }
            }
            else
            {
                for (auto& pad_part : pad_)
                {
                    pad_part.move(-0.5, 0);
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if (pad_[0].getGlobalBounds().left > 0)
            {
                for (auto& pad_part : pad_)
                {
                    pad_part.move(-speed_[0] * time.asSeconds(), 0);
                }
            }
            else
            {
                for (auto& pad_part : pad_)
                {
                    pad_part.move(0.5, 0);
                }
            }
        }
    }

}

int Player::cached_gift(std::vector<Enemy_block>& enemy_blocks) // from 1 to 9
{
    for (auto& drop : enemy_blocks)
    {
        for (auto& pad_part : pad_)
        {
            if (pad_part.getGlobalBounds().intersects(drop.getGlobalBounds()))
            {
                drop.disapear();
                return drop.gift();
            }
        }
    }
    return 0;
}

void Player::make_it_bigger()
{
    for (auto& pad_part : pad_) { pad_part.scale(1.25, 1); }

    pad_[2].setPosition(pad_[2].getGlobalBounds().left - ((pad_[2].getGlobalBounds().width - pad_[2].getGlobalBounds().width * 0.8) / 2), pad_[2].getGlobalBounds().top);
    pad_[1].setPosition(pad_[2].getGlobalBounds().left - pad_[1].getGlobalBounds().width, pad_[1].getGlobalBounds().top);
    pad_[0].setPosition(pad_[1].getGlobalBounds().left - pad_[0].getGlobalBounds().width, pad_[0].getGlobalBounds().top);
    pad_[3].setPosition(pad_[2].getGlobalBounds().left + pad_[2].getGlobalBounds().width, pad_[3].getGlobalBounds().top);
    pad_[4].setPosition(pad_[3].getGlobalBounds().left + pad_[3].getGlobalBounds().width, pad_[4].getGlobalBounds().top);
    changing_size_[0] = 1;
    changing_size_[1] = 5.0;
}

void Player::make_it_smaller()
{
    for (auto& pad_part : pad_) { pad_part.scale(0.8, 1); }

    pad_[2].setPosition(pad_[2].getGlobalBounds().left - ((pad_[2].getGlobalBounds().width - pad_[2].getGlobalBounds().width * 1.2) / 2), pad_[2].getGlobalBounds().top);
    pad_[1].setPosition(pad_[2].getGlobalBounds().left - pad_[1].getGlobalBounds().width, pad_[1].getGlobalBounds().top);
    pad_[0].setPosition(pad_[1].getGlobalBounds().left - pad_[0].getGlobalBounds().width, pad_[0].getGlobalBounds().top);
    pad_[3].setPosition(pad_[2].getGlobalBounds().left + pad_[2].getGlobalBounds().width, pad_[3].getGlobalBounds().top);
    pad_[4].setPosition(pad_[3].getGlobalBounds().left + pad_[3].getGlobalBounds().width, pad_[4].getGlobalBounds().top);
    changing_size_[0] = -1;
    changing_size_[1] = 5.0;
}

void Player::make_it_faster()
{
    speed_[0] += 700;
    speed_[1] = 10.0;
}

void Player::make_it_slower()
{
    speed_[0] -= 700;
    speed_[1] = 0.0;
}

void Player::make_it_stop()
{
    stop_[0] = 1.0;
    stop_[1] = 1.0;
}

void Player::make_it_move()
{
    stop_[0] = 0.0;
    stop_[1] = 0.0;
}

bool Player::get_speed_is_changed() { return speed_[0] != 700.0; }

double Player::get_speed_time() { return speed_[1]; }

bool Player::get_size_is_changed() { return changing_size_[0] != 0.0; }

double Player::get_changing_size_time() { return changing_size_[1]; }

bool Player::get_stop_is_changed() { return stop_[0] != 0.0; }

double Player::get_stop_time() { return stop_[1]; }
