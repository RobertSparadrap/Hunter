/*
** EPITECH PROJECT, 2019
** my_hunter
** File description:
** 
*/

#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <stdlib.h>
#include <stdio.h>

sfRenderWindow *create_window()
{
    sfRenderWindow *window;
    sfVideoMode video_mode;

    video_mode.height = 1080;
    video_mode.width = 1920;
    window = sfRenderWindow_create(video_mode, "picture/My Luigi's Mansion", sfDefaultStyle, NULL);
    return window;
}

void event_close(sfRenderWindow *window)
{
    sfEvent event;
    sfEventType type;
    while (sfRenderWindow_pollEvent(window, &event))
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
}

sfSprite *get_fond(sfRenderWindow *window, char const *filepath)
{
    sfTexture *texture_f;
    sfSprite *sprite_f;

    texture_f = sfTexture_createFromFile(filepath, NULL);
    sprite_f = sfSprite_create();
    sfSprite_setTexture(sprite_f, texture_f, sfTrue);
    return sprite_f;
}

void get_music(char const *filepath)
{
    sfMusic *music = sfMusic_createFromFile(filepath);
    sfMusic_play(music);
}

sfSprite *get_sprite(sfRenderWindow *window, char const *filepath)
{
    sfTexture *texture_g = sfTexture_createFromFile(filepath, NULL);
    sfSprite *sprite_g = sfSprite_create();
    sfSprite_setTexture(sprite_g, texture_g, sfTrue);
    return sprite_g;
}

void sprite_ghost(sfSprite *sprite_g, sfIntRect rect, sfVector2f vec)
{
    sfSprite_setPosition(sprite_g, vec);
    sfSprite_setTextureRect(sprite_g, rect);
}

sfSprite *get_scope(sfRenderWindow *window)
{
    sfVector2f scale;
    sfTexture *texture_s;
    sfSprite *sprite_s;

    scale.x = 0.3;
    scale.y = 0.3;
    texture_s = sfTexture_createFromFile("picture/scope.png", NULL);
    sprite_s = sfSprite_create();
    sfSprite_setTexture(sprite_s, texture_s, sfTrue);
    sfSprite_setScale(sprite_s, scale);
    return sprite_s;
}

void draw_game(sfRenderWindow *window, sfSprite *sprite_f, sfSprite *sprite_g, sfSprite *sprite_s, sfIntRect rect, sfVector2f vec, int pv)
{
    sfVector2f cursor_position;
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawSprite(window, sprite_f, NULL);
    sprite_ghost(sprite_g, rect, vec);
    if (pv > 0)
        sfRenderWindow_drawSprite(window, sprite_g, NULL);
    cursor_position.x = sfMouse_getPosition(window).x-63;
    cursor_position.y = sfMouse_getPosition(window).y-63;
    sfSprite_setPosition(sprite_s, cursor_position);
    sfRenderWindow_drawSprite(window, sprite_s, NULL);
}

int sprite_mv(int left, sfClock *clock)
{
    sfTime time;

    time = sfClock_getElapsedTime(clock);
    if (time.microseconds >= 1000000 / 3.5) {
        if (left == 1126)
            left = 726;
        else
            left += 200;
        sfClock_restart(clock);
    }
    return left;
}

int show_pv(sfRenderWindow *window, int pv, sfText *text)
{
    sfVector2f position = {1870, 0};
    char str[3] = {0};

    str[0] = (pv % 10 + '0');
    sfText_setPosition(text, position);
    sfText_setString(text, str);
    sfRenderWindow_drawText(window, text, NULL);
}

int lives(sfVector2f vec, int i, float v, int score, int a, int pv, sfRenderWindow *window, sfText *text)
{
    vec.x -= v;
    if (i == 0) {
        vec.x = 2500;
        vec.y = rand() % 800;
    }
    if (vec.x <= -180) {
        pv -= 1;
        vec.x = 2500;
        vec.y = rand() % 789;
    }
    if (score >= 5) {
        if (vec.y == 0)
            a = 1;
        vec.y += a;
    }
    return pv;
}

sfVector2f move(sfVector2f vec, int i, float v, int score, int *a, sfTime time_g, sfClock *clock_g)
{
    sfVector2f position = {1870, 0};
    char str[3] = {0};
    time_g = sfClock_getElapsedTime(clock_g);
    if (time_g.microseconds >= 10000 / 6) {
        vec.x -= v;
        if (vec.x <= -180) {
            vec.x = 2500;
            vec.y = rand() % 800;
        }
        sfClock_restart(clock_g);
    }
    if (i == 0) {
        vec.x = 2500;
        vec.y = rand() % 800;
    }
//    if (vec.x <= -180) {
//        vec.x = 2500;
//        vec.y = rand() % 800;
//    }
    if (score >= 5) {
        if (vec.y == 0)
            *a = 1;
        if (vec.y == 790)
            *a = -1;
        vec.y += *a;
    }
    return vec;
}

float velocity(float v, int i)
{
    if (i == 0)
        v += 0.3;
    return v;
}

sfVector2f get_cursor(sfRenderWindow *window)
{
    sfVector2f cursor_position;
    sfVector2i cursor_position2;

    cursor_position2 = sfMouse_getPosition(window);
    cursor_position.x = (float) cursor_position2.x;
    cursor_position.y = (float) cursor_position2.y;
    return cursor_position;
}

int shoot(sfRenderWindow *window, sfEvent event, sfEventType type, sfSprite *sprite_g)
{
    int score = 0;
    int r;
    sfVector2f cursor_position, O;
    int i = 1;

    if (event.type == sfEvtClosed)
        sfRenderWindow_close(window);
    if (event.type == sfEvtMouseButtonPressed) {
        cursor_position = get_cursor(window);
        O = sfSprite_getPosition(sprite_g);
        r = 160 / 2;
        if (((O.x + 100) - cursor_position.x) * ((O.x + 100) - cursor_position.x) + ((O.y + 50) - cursor_position.y) * ((O.y + 50) - cursor_position.y) <= r * r)
            i = 0;
    }
    return i;
}

sfIntRect death(sfRenderWindow *window, int i, sfSprite *sprite_s, sfSprite *sprite_n, sfClock *clock, sfIntRect rect_d)
{
    sfTime time;
    
    if (i == 0) {
        time = sfClock_getElapsedTime(clock);
        if (time.microseconds >= 1000000 / 6) {
            if (rect_d.left == 600) {
                rect_d.left = 0;
                rect_d.top = 150;
            }
            else
                rect_d.left += 300;
            sfClock_restart(clock);
        }
    }
    return rect_d;
}

sfText *getText()
{
    sfText *text;
    sfFont *font;
    font = sfFont_createFromFile("picture/SuperMario256.ttf");
    text = sfText_create();
    sfText_setString(text, "0");
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 70);
    return text;
}

int show_score(int i, sfText *text_score, int score)
{
    char str[3] = {0};

    if (i == 0) {
        score += 1;
        if (score > 9) {
            str[0] = (score / 10 + '0');
            str[1] = (score % 10 + '0');
        }
        else
            str[0] = (score % 10 + '0');
        sfText_setString(text_score, str);
    }
    return score;
}

void show_game_over(int pv, sfSprite *sprite_f, sfSprite *sprite_g, sfRenderWindow *window, sfVector2f cursor_position, sfSprite *sprite_s, int i, int score, sfText *text)
{
    char *str = malloc(10);
    sfText *text_score = getText();
    sfVector2f game_over = {460, 400}, scale_go;
    sfEvent event;
    sfEventType type;

    if (pv <= 0) {
        sfSprite_destroy(sprite_f);
        sfSprite_destroy(sprite_g);
        while (sfRenderWindow_isOpen(window)) {
            while (sfRenderWindow_pollEvent(window, &event))
                if (event.type == sfEvtClosed)
                    sfRenderWindow_close(window);
            score = show_score(i, text_score, score);
            sfText_setString(text_score, str);
            scale_go.x = 2.1;
            scale_go.y = 2.1;
            str = "Game Over";
            cursor_position = get_cursor(window);
            cursor_position.x -= 63;
            cursor_position.y -= 63;
            sfSprite_setPosition(sprite_s, cursor_position);
            sfRenderWindow_clear(window, sfBlack);
            sfText_setPosition(text, game_over);
            sfText_setScale(text, scale_go);
            sfRenderWindow_drawText(window, text, NULL);
            sfRenderWindow_drawText(window, text_score, NULL);
            sfRenderWindow_drawSprite(window, sprite_s, NULL);
            sfRenderWindow_display(window);
        }
    }
}

void game(sfRenderWindow *window)
{
    int left_d = 0, up_d = -90;
    sfIntRect rect_d = {left_d, up_d, 330, 290};

    sfTime time_g;
    sfClock *clock_g = sfClock_create();
    sfText *text = getText(), *text_pv = getText();
    int left = 726, r, i = 1, score = 0, a = -1, pv = 3;
    float v = 1, x = 2000;
    int y = rand() % 800;
    sfIntRect rect = {left, 681, 187, 159};
    sfVector2f vec = {x, y}, cursor_position, O, game_over = {460, 400}, scale_go;
    sfEvent event;
    sfEventType type;
    sfClock *clock = sfClock_create();
    sfClock *clock_d = sfClock_create();
    sfSprite *sprite_f = get_fond(window, "picture/mansion.png");
    sfSprite *sprite_g = get_sprite(window, "picture/ghost2.png");
    sfSprite *sprite_n = get_sprite(window, "picture/nuage(1).png");
    sfSprite *sprite_s = get_scope(window);
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event))
            i = shoot(window, event, type, sprite_g);
        pv = lives(vec, i, v, score, a, pv, window, text);
        draw_game(window, sprite_f, sprite_g, sprite_s, rect, vec, pv);

//        rect_d = death(window, i, sprite_s, sprite_n, clock_d, rect_d);

//        sfSprite_setTextureRect(sprite_n, rect_d);
//        sfSprite_setPosition(sprite_n, sfSprite_getPosition(sprite_s));
//        sfRenderWindow_drawSprite(window, sprite_n, NULL);

        rect.left = sprite_mv(rect.left, clock);
        score = show_score(i, text, score);
        show_pv(window, pv, text_pv);
        sfRenderWindow_drawText(window, text, NULL);
        sfRenderWindow_display(window);
        show_game_over(pv, sprite_f, sprite_g, window, cursor_position, sprite_s, i , score, text);
        v = velocity(v, i);
        vec = move(vec, i, v, score, &a, time_g, clock_g);
        i = 1;
    }
}

void start_game(sfRenderWindow *window, sfSprite *sprite_quit, sfSprite *sprite_m, sfSprite *sprite_play)
{
    sfEvent event;
    sfEventType type;
    sfVector2f O, cursor_position;
    int r;
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (event.type == sfEvtMouseButtonPressed) {
            cursor_position = get_cursor(window);
            O = sfSprite_getPosition(sprite_quit);
            r = 150 / 2;
            if (((O.x + 100) - cursor_position.x) * ((O.x + 100) - cursor_position.x) + ((O.y + 50) - cursor_position.y) * ((O.y + 50) - cursor_position.y) <= r * r)
                sfRenderWindow_close(window);
            if (cursor_position.x >= 125 && cursor_position.x <= 920 && cursor_position.y >= 820 && cursor_position.y <= 980) {
                sfSprite_destroy(sprite_m);
                sfSprite_destroy(sprite_play);
                game(window);
            }
        }
    }
}

void menu(sfRenderWindow *window)
{
    sfSprite *sprite_m = get_fond(window, "picture/menu.jpg");
    sfSprite *sprite_s = get_scope(window);
    sfSprite *sprite_play = get_sprite(window, "picture/play.png");
    sfSprite *sprite_quit = get_sprite(window, "picture/quit.png");
    sfVector2f play = {80, 760}, quit = {1200, 760}, O, cursor_position;
    while (sfRenderWindow_isOpen(window)) {
        sfSprite_setPosition(sprite_play, play);
        sfSprite_setPosition(sprite_quit, quit);
        cursor_position = get_cursor(window);
        cursor_position.x -= 63;
        cursor_position.y -= 63;
        sfSprite_setPosition(sprite_s, cursor_position);
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawSprite(window, sprite_m, NULL);
        sfRenderWindow_drawSprite(window, sprite_play, NULL);
        sfRenderWindow_drawSprite(window, sprite_quit, NULL);
        sfRenderWindow_drawSprite(window, sprite_s, NULL);
        sfRenderWindow_display(window);
        start_game(window, sprite_quit, sprite_m, sprite_play);
    }
}

void help()
{
    my_printf("%s\n", "\n Oh non Luigi est en grand danger !");
    my_printf("%s\n", "Visez les boo avec votre viseur et cliquez sur la souris pour aider Luigi a vaincre les boo.");
    my_printf("%s\n", "Luigi ne peut pas gerer plus de 2 boo, ce qui signifie que vous aviez droit a 2 fails avant que Luigi ne se fasse manger.");
    my_printf("%s\n", "\n Sur la page de menu vous pouvez soit cliquer sur play pour aider Luigi, soit le laisser tomber en cliquant sur quit 3:)");
    my_printf("%s\n", "Dans le jeu vous y verrez en haut a gauche votre score et en haut a droite le nombre de vie de Luigi.");
    my_printf("%s\n", "Sur ce, bonne chance ;) \n");
}

int main(int argc, char **argv)
{
    if (argc == 2) {
        if (argv[1][0] == '-' && argv[1][1] == 'h')
            help();
        else
            return 84;
    }
    else {
        sfMusic *music = sfMusic_createFromFile("picture/Theme.ogg");
        sfRenderWindow *window = create_window();
        sfMusic_play(music);
        sfRenderWindow_setMouseCursorVisible(window, sfFalse);
        menu(window);
        sfMusic_pause(music);
        sfMusic_destroy(music);
        sfRenderWindow_destroy(window);
    }
}
