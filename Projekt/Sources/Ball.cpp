#include "..\Headers\Ball.h"

#include <iostream>

Ball::Ball(const std::map<std::string, sf::Texture>& textures, const std::map<std::string, sf::SoundBuffer>& samples, sf::Window& window, const int difficulty) : Sprite()
{
    setTexture(textures.at("blue_ball"));
    setScale(0.5, 0.5);
    setPosition(window.getSize().x / 2 - getGlobalBounds().width / 2, window.getSize().y / 2 - getGlobalBounds().height / 2);
    sample_on_touch_.setBuffer(samples.at("pad_bounce"));
    switch (difficulty)
    {
    case 1:
        speed_x_ = 200;
        speed_y_ = 200;
        begin_speed_ = sqrt(pow(speed_x_, 2) + pow(speed_y_, 2));
    case 3:
        speed_x_ = 400;
        speed_y_ = 400;
        begin_speed_ = sqrt(pow(speed_x_, 2) + pow(speed_y_, 2));
    }
}

bool Ball::step(sf::Time time, const sf::Window& window, Player& player, std::vector<Enemy_block>& enemy_blocks, std::map<std::string, sf::Texture>& drops, int& points)
{
    if (changed_speed_ != 0)
    {
        timer_changed_speed_ -= time.asSeconds();
        if (timer_changed_speed_ <= 0.0)
        {
            timer_changed_speed_ = 0.0;

            if (changed_speed_ == 1) { make_it_slower_(); }
            else if (changed_speed_ == -1) { make_it_faster_(); }

            changed_speed_ = 0;
        }
    }

    if (!do_loose_on_bottom_bounce_)
    {
        timer_no_loose_ -= time.asSeconds();
        if (timer_no_loose_ <= 0.0)
        {
            timer_no_loose_ = 0.0;

            do_loose_on_bottom_bounce_ = true;
        }
    }

    if (getGlobalBounds().left <= 0) { speed_x_ *= -1; move(0.1, 0); sample_on_touch_.play(); }
    else if (getGlobalBounds().left + getGlobalBounds().width >= window.getSize().x) { speed_x_ *= -1; move(-0.1, 0); sample_on_touch_.play(); }

    if (getGlobalBounds().top <= 0) { speed_y_ *= -1; move(0, 0.1); sample_on_touch_.play(); }
    else if (getGlobalBounds().top + getGlobalBounds().height >= window.getSize().y) { sample_on_touch_.play();  return handle_bottom_touch(); }

    for (int i = 0; i < player.pad_size(); i++)
    {
        if (getGlobalBounds().intersects(player.pad(i).getGlobalBounds()))
        {
            double x, y;
            std::tie(x, y) = player.pad(i).bounce(speed_x_, speed_y_, begin_speed_);
            std::cout << x << " " << y << std::endl;
            move(x / 100, y / 100);
            speed_x_ = x;
            speed_y_ = y;
            sample_on_touch_.play();

            while (sqrt(pow(speed_x_, 2) + pow(speed_y_, 2)) > begin_speed_)
            {
                if (speed_x_ > 0) { speed_x_ -= 0.2; }
                else { speed_x_ += 0.2; }
                if (speed_y_ > 0) { speed_y_ -= 0.2; }
                else { speed_y_ += 0.2; }
            }

            if (abs(speed_x_) < abs(speed_y_) / 4)
            {
                while (abs(speed_x_) < abs(speed_y_) / 4)
                {
                    if (speed_x_ > 0) { speed_x_ += 0.1; }
                    else { speed_x_ -= 0.1; }
                    if (speed_y_ > 0) { speed_y_ += 0.1; }
                    else { speed_y_ -= 0.1; }
                }
            }
            else if (abs(speed_y_) < abs(speed_x_) / 4)
            {
                while (abs(speed_y_) < abs(speed_x_) / 4)
                {
                    if (speed_y_ > 0) { speed_y_ += 0.1; }
                    else { speed_y_ -= 0.1; }
                    if (speed_x_ > 0) { speed_x_ += 0.1; }
                    else { speed_x_ -= 0.1; }
                }
            }
            std::cout << speed_x_ << " " << speed_y_ << std::endl;
            break;
        }
    }

    for (auto& enemy_block : enemy_blocks)
    {
        if (getGlobalBounds().intersects(enemy_block.getGlobalBounds()) && enemy_block.colision())
        {
            double approxima = 1.5;
            if (getGlobalBounds().left <= enemy_block.getGlobalBounds().left + enemy_block.getGlobalBounds().width && getGlobalBounds().left >= enemy_block.getGlobalBounds().left + enemy_block.getGlobalBounds().width - approxima) { speed_x_ *= -1; }
            else if (getGlobalBounds().left + getGlobalBounds().width >= enemy_block.getGlobalBounds().left && getGlobalBounds().left + getGlobalBounds().width <= enemy_block.getGlobalBounds().left + approxima) { speed_x_ *= -1; }
            else if (getGlobalBounds().top <= enemy_block.getGlobalBounds().top + enemy_block.getGlobalBounds().height && getGlobalBounds().top >= enemy_block.getGlobalBounds().top + enemy_block.getGlobalBounds().height - approxima) { speed_y_ *= -1; }
            else if (getGlobalBounds().top + getGlobalBounds().height >= enemy_block.getGlobalBounds().top && getGlobalBounds().top + getGlobalBounds().height <= enemy_block.getGlobalBounds().top + approxima) { speed_y_ *= -1; }

            enemy_block.bounce(drops);
            if (!enemy_block.am_i_alive()) { points += enemy_block.points(); }
            break;
        }
    }

    move(speed_x_ * time.asSeconds(), speed_y_ * time.asSeconds());
    return false;
}

bool Ball::handle_bottom_touch()
{
    if (do_loose_on_bottom_bounce_) { return true; }
    else
    {
        speed_y_ *= -1;
        move(0, -0.1);
        return false;
    }
}

double Ball::speed_x() { return speed_x_; }

double Ball::speed_y() { return speed_y_; }

void Ball::set_no_lose()
{
    do_loose_on_bottom_bounce_ = false;
    timer_no_loose_ = 9.0;
}

double Ball::get_timer_no_loose() { return timer_no_loose_; }

bool Ball::get_loose_is_changed() { return !do_loose_on_bottom_bounce_; }

int Ball::changed_speed() { return changed_speed_; }

double Ball::get_timer_changed_speed() { return timer_changed_speed_; }

void Ball::make_it_faster_()
{
    if (changed_speed_ != 1)
    {
        speed_x_ *= 1.25;
        speed_y_ *= 1.25;
        begin_speed_ = sqrt(pow(speed_x_, 2) + pow(speed_y_, 2));
        changed_speed_ += 1;
    }
    timer_changed_speed_ = 5.0;
}

void Ball::make_it_slower_()
{
    if (changed_speed_ != -1)
    {
        speed_x_ *= 0.8;
        speed_y_ *= 0.8;
        begin_speed_ = sqrt(pow(speed_x_, 2) + pow(speed_y_, 2));
        changed_speed_ -= 1;
    }
    timer_changed_speed_ = 5.0;
}
