#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../inc/string_functions.h"
#include "SFML/Graphics/Texture.h"
#include "SFML/Graphics.h"
#include "SFML/Window.h"
#include "SFML/System.h"
#include "SFML/Audio.h"
#include "SFML/System/Vector2.h"

typedef struct s_Character {
	float dx;
 	float dy;

 	bool onGround;
 	double hp;
    
 	float Speed;

 	sfSprite *SpriteHpBar;

 	sfSprite *Sprite;

} t_Character;


typedef struct s_NPC {
    float dx;
 	float dy;
    sfSprite *Sprite;

}   t_NPC;

typedef struct s_Quest{
    bool isActive;
    sfText *text;
    bool isComplete;
}   t_Quest;

typedef struct s_Enemy{
    double hp;
    float dmg;
    float dx;
    float dy;
    bool isDead;
    sfSprite *Sprite;
}   t_Enemy;

int main()
{
    sfRenderWindow* main_window;
    sfVideoMode mode = {1920, 1080, 60};
    
    main_window = sfRenderWindow_create(mode, "CSFML WORKS", sfResize | sfClose, NULL);
    // sfRenderWindow_setMouseCursorVisible(main_window, sfFalse);
    if (!main_window)
        return 1;
    sfRenderWindow_setVerticalSyncEnabled(main_window, sfTrue);
    
    sfVector2f offset;

    sfTexture *character_texture = sfTexture_createFromFile("resource/Warrior/Movement/Idle/0.png",NULL);
    sfSprite *character_sprite = sfSprite_create();
    sfSprite_setTexture(character_sprite,character_texture,sfFalse);
    sfIntRect IntRect;
    //стартовая позиция
    // IntRect.left = 10;
    // IntRect.top = 55;
    //IntRect.width = 1500; 
    // IntRect.height = 35;
    // sfSprite_setTextureRect(character_sprite, IntRect);
    
    t_NPC NPC;
    sfVector2f npc_coords;
    sfTexture *npc_texture = sfTexture_createFromFile("resource/npc/0.png",NULL);
    sfSprite *npc_sprite = sfSprite_create();
    sfSprite_setTexture(npc_sprite,npc_texture,sfFalse);
    NPC.dx = 1100;
    NPC.dy = 535;
    npc_coords.x = NPC.dx;
    npc_coords.y = NPC.dy;
    NPC.Sprite = npc_sprite;
    sfSprite_setPosition(NPC.Sprite, npc_coords);

    //CHARACTER INIT --------------------------------------------
    t_Character Character;
    Character.onGround = false;
    Character.dx = 150;
    Character.dy = 100;
    Character.hp = 20.0;
    Character.Sprite = character_sprite;
    sfVector2f character_coords;
    offset.x = 0;
    offset.y = 0;
    character_coords.x = Character.dx;
    character_coords.y = Character.dy;
    sfSprite_setPosition(Character.Sprite, character_coords);
    // -----------------------------------------------------------
    float current_frame = 0;

    // TEXTURES INIT -----------------------------------------------------------
    sfTexture **character_texture_mas_r = malloc(sizeof(sfTexture *)*8);

    character_texture_mas_r[0] = sfTexture_createFromFile("resource/Warrior/Movement/Run_right/0.png",NULL);
    character_texture_mas_r[1] = sfTexture_createFromFile("resource/Warrior/Movement/Run_right/1.png",NULL);
    character_texture_mas_r[2] = sfTexture_createFromFile("resource/Warrior/Movement/Run_right/2.png",NULL);
    character_texture_mas_r[3] = sfTexture_createFromFile("resource/Warrior/Movement/Run_right/3.png",NULL);
    character_texture_mas_r[4] = sfTexture_createFromFile("resource/Warrior/Movement/Run_right/4.png",NULL);
    character_texture_mas_r[5] = sfTexture_createFromFile("resource/Warrior/Movement/Run_right/5.png",NULL);
    character_texture_mas_r[6] = sfTexture_createFromFile("resource/Warrior/Movement/Run_right/6.png",NULL);
    character_texture_mas_r[7] = sfTexture_createFromFile("resource/Warrior/Movement/Run_right/7.png",NULL);

    sfTexture **character_texture_mas_l = malloc(sizeof(sfTexture *)*8);

    character_texture_mas_l[0] = sfTexture_createFromFile("resource/Warrior/Movement/Run_left/0.png",NULL);
    character_texture_mas_l[1] = sfTexture_createFromFile("resource/Warrior/Movement/Run_left/1.png",NULL);
    character_texture_mas_l[2] = sfTexture_createFromFile("resource/Warrior/Movement/Run_left/2.png",NULL);
    character_texture_mas_l[3] = sfTexture_createFromFile("resource/Warrior/Movement/Run_left/3.png",NULL);
    character_texture_mas_l[4] = sfTexture_createFromFile("resource/Warrior/Movement/Run_left/4.png",NULL);
    character_texture_mas_l[5] = sfTexture_createFromFile("resource/Warrior/Movement/Run_left/5.png",NULL);
    character_texture_mas_l[6] = sfTexture_createFromFile("resource/Warrior/Movement/Run_left/6.png",NULL);
    character_texture_mas_l[7] = sfTexture_createFromFile("resource/Warrior/Movement/Run_left/7.png",NULL);

    sfTexture **character_texture_mas_afk = malloc(sizeof(sfTexture *)*8);

    character_texture_mas_afk[0] = sfTexture_createFromFile("resource/Warrior/Movement/Idle/0.png",NULL);
    character_texture_mas_afk[1] = sfTexture_createFromFile("resource/Warrior/Movement/Idle/1.png",NULL);
    character_texture_mas_afk[2] = sfTexture_createFromFile("resource/Warrior/Movement/Idle/2.png",NULL);
    character_texture_mas_afk[3] = sfTexture_createFromFile("resource/Warrior/Movement/Idle/3.png",NULL);
    character_texture_mas_afk[4] = sfTexture_createFromFile("resource/Warrior/Movement/Idle/4.png",NULL);
    character_texture_mas_afk[5] = sfTexture_createFromFile("resource/Warrior/Movement/Idle/5.png",NULL);

    sfTexture **character_texture_mas_jump = malloc(sizeof(sfTexture *)*6);

    character_texture_mas_jump[0] = sfTexture_createFromFile("resource/Warrior/Jump/0.png",NULL);
    character_texture_mas_jump[1] = sfTexture_createFromFile("resource/Warrior/Jump/1.png",NULL);
    character_texture_mas_jump[2] = sfTexture_createFromFile("resource/Warrior/Jump/2.png",NULL);
    character_texture_mas_jump[3] = sfTexture_createFromFile("resource/Warrior/Fall/0.png",NULL);
    character_texture_mas_jump[4] = sfTexture_createFromFile("resource/Warrior/Fall/1.png",NULL);
    character_texture_mas_jump[5] = sfTexture_createFromFile("resource/Warrior/Fall/2.png",NULL);

    sfTexture **character_texture_mas_crouch = malloc(sizeof(sfTexture *)*4);
    character_texture_mas_crouch[0] = sfTexture_createFromFile("resource/Warrior/Crouch/1.png",NULL);
    character_texture_mas_crouch[1] = sfTexture_createFromFile("resource/Warrior/Crouch/2.png",NULL);
    character_texture_mas_crouch[2] = sfTexture_createFromFile("resource/Warrior/Crouch/3.png",NULL);
    character_texture_mas_crouch[3] = sfTexture_createFromFile("resource/Warrior/Crouch/4.png",NULL);

    sfTexture **npc_texture_mas_idle = malloc(sizeof(sfTexture *)*6);
    npc_texture_mas_idle[0] = sfTexture_createFromFile("resource/npc/0.png",NULL);
    npc_texture_mas_idle[1] = sfTexture_createFromFile("resource/npc/1.png",NULL);
    npc_texture_mas_idle[2] = sfTexture_createFromFile("resource/npc/2.png",NULL);
    npc_texture_mas_idle[3] = sfTexture_createFromFile("resource/npc/3.png",NULL);
    npc_texture_mas_idle[4] = sfTexture_createFromFile("resource/npc/4.png",NULL);
    npc_texture_mas_idle[5] = sfTexture_createFromFile("resource/npc/5.png",NULL);

    sfTexture **character_texture_mas_attack = malloc(sizeof(sfTexture *)*12);
    character_texture_mas_attack[0] = sfTexture_createFromFile("resource/Warrior/Attack/0.png",NULL);
    character_texture_mas_attack[1] = sfTexture_createFromFile("resource/Warrior/Attack/1.png",NULL);
    character_texture_mas_attack[2] = sfTexture_createFromFile("resource/Warrior/Attack/2.png",NULL);
    character_texture_mas_attack[3] = sfTexture_createFromFile("resource/Warrior/Attack/3.png",NULL);
    character_texture_mas_attack[4] = sfTexture_createFromFile("resource/Warrior/Attack/4.png",NULL);
    character_texture_mas_attack[5] = sfTexture_createFromFile("resource/Warrior/Attack/5.png",NULL);
    character_texture_mas_attack[6] = sfTexture_createFromFile("resource/Warrior/Attack/6.png",NULL);
    character_texture_mas_attack[7] = sfTexture_createFromFile("resource/Warrior/Attack/7.png",NULL);
    character_texture_mas_attack[8] = sfTexture_createFromFile("resource/Warrior/Attack/8.png",NULL);
    character_texture_mas_attack[9] = sfTexture_createFromFile("resource/Warrior/Attack/9.png",NULL);
    character_texture_mas_attack[10] = sfTexture_createFromFile("resource/Warrior/Attack/10.png",NULL);
    character_texture_mas_attack[11] = sfTexture_createFromFile("resource/Warrior/Attack/11.png",NULL);


    sfTexture *background_t1 = sfTexture_createFromFile("resource/BG_lvl1.png",NULL);
    sfSprite *background_s1 = sfSprite_create();
    sfSprite_setTexture(background_s1,background_t1,sfFalse);

    sfTexture *background_t2 = sfTexture_createFromFile("resource/BG_lvl2.png",NULL);
    sfSprite *background_s2 = sfSprite_create();
    sfSprite_setTexture(background_s2,background_t2,sfFalse);

    sfTexture *item_for_quest_t = sfTexture_createFromFile("resource/item_for_quest.png",NULL);
    sfSprite *item_for_quest_s = sfSprite_create();
    sfSprite_setTexture(item_for_quest_s,item_for_quest_t,sfFalse);
    sfVector2f item_pos;
    item_pos.x = 820;
    item_pos.y = 640;
    sfSprite_setPosition(item_for_quest_s, item_pos);
    
    // -------------------------------------------------------------------------------------------------------

    int ground = 507;

    int i = 0;
    float time;
    sfVector2i pos;
    pos.x = 0;
    pos.y = 0;
    sfClock *clock = sfClock_create(); 

    float cur_frame_npc = 0;
    bool isMap1Active = true;


    sfText *npc_replica1 = sfText_create();
    sfFont *font = sfFont_createFromFile("resource/fonts/sunday.ttf");
    sfText_setCharacterSize(npc_replica1, 15);
    sfText_setFont(npc_replica1, font);
    sfText_setColor(npc_replica1, sfRed);
    sfText_setStyle(npc_replica1,sfTextBold);
    sfText_setString(npc_replica1,"Oh, I see you have some health problems, dont yah? \nI could help you, bring the red bottle \nfrom the next room to me and i`ll help you.");
    sfVector2f text_coords;
    text_coords.x = npc_coords.x - 100;
    text_coords.y = npc_coords.y - 80;
    sfText_setPosition(npc_replica1, text_coords);
    
    
    // char npc_replic2[200] = "There you go, thanks. But i have an other quest for you, \ncan you please beat that monster that is hanging around in that room?";
    
    sfText *npc_replica2 = sfText_create();
    sfText_setCharacterSize(npc_replica2, 15);
    sfText_setFont(npc_replica2, font);
    sfText_setColor(npc_replica2, sfGreen);
    sfText_setStyle(npc_replica2,sfTextBold);
    sfText_setString(npc_replica2,"There you go, thanks. But i have an other quest for you, \ncan you please beat that monster that is hanging around in that room?");
    sfText_setPosition(npc_replica2, text_coords);
    
    
    
    // char npc_replic3[200] = "Oh, thanks a lot. Here, take some gold for your help.";
    sfText *npc_replica3 = sfText_create();
    sfText_setCharacterSize(npc_replica3, 15);
    sfText_setFont(npc_replica3, font);
    sfText_setColor(npc_replica3, sfRed);
    sfText_setStyle(npc_replica3,sfTextBold);
    sfText_setString(npc_replica3,"Oh, thanks a lot. Here, take some gold for your help.");
    sfText_setPosition(npc_replica3, text_coords);


    sfBool isIntersects_with_npc = sfFalse;

    t_Quest quest_1;
    quest_1.isActive = false;

    sfText *quest_text = sfText_create();
    sfText_setCharacterSize(quest_text, 11);
    sfText_setFont(quest_text, font);
    sfText_setColor(quest_text, sfRed);
    sfText_setStyle(quest_text,sfTextBold);
    sfText_setString(quest_text,"1. Go to the next room and \nfind a red bottle.");
    text_coords.x = 10;
    text_coords.y = 30;
    sfText_setPosition(quest_text, text_coords);
    quest_1.text = quest_text;
    quest_1.isComplete = false;


    t_Quest quest_2;
    quest_2.isActive = false;
    sfText *quest_text2 = sfText_create();
    sfText_setCharacterSize(quest_text2, 11);
    sfText_setFont(quest_text2, font);
    sfText_setColor(quest_text2, sfRed);
    sfText_setStyle(quest_text2,sfTextBold);
    sfText_setString(quest_text2,"2. Go to the next room and \nbeat a monster.");
    text_coords.x = 10;
    text_coords.y = 30;
    sfText_setPosition(quest_text2, text_coords);
    quest_2.text = quest_text2;
    quest_2.isComplete = false;


// QUEST LIST -------------------------------------------------------------------------------------------------------   

    sfImage *qlist_bg = sfImage_createFromFile("resource/missionbg.jpg");
    sfTexture *qlist_tx = sfTexture_createFromImage(qlist_bg, NULL);
    sfSprite *qlist_spt = sfSprite_create();
    sfSprite_setTexture(qlist_spt,qlist_tx, sfFalse);
    sfVector2f scale_qlist;
    scale_qlist.x = 0.8;
    scale_qlist.y = 0.8;
    sfSprite_setScale(qlist_spt, scale_qlist);
    // sfIntRect char_rect = sfSprite_getTextureRect(Character.Sprite);

// ------------------------------------------------------------------------------------------------------------------


//ENEMY INIT --------------------------------------------
    sfTexture *enemy_texture = sfTexture_createFromFile("resource/mob/idle/0.png",NULL);
    sfSprite *enemy_sprite = sfSprite_create();
    sfSprite_setTexture(enemy_sprite,enemy_texture,sfFalse);
    t_Enemy Enemy;
    Enemy.dx = 1500;
    Enemy.dy = 570;
    Enemy.hp = 100.0;
    Enemy.isDead = false;
    Enemy.Sprite = enemy_sprite;
    sfVector2f enemy_coords;
    enemy_coords.x = Enemy.dx;
    enemy_coords.y = Enemy.dy;
    sfSprite_setPosition(Enemy.Sprite, enemy_coords);
    float cur_frame_enemy = 0;

    sfTexture **enemy_textures_attack = malloc(sizeof(sfTexture *)*17);
    enemy_textures_attack[0] = sfTexture_createFromFile("resource/mob/attack/0.png",NULL);
    enemy_textures_attack[1] = sfTexture_createFromFile("resource/mob/attack/1.png",NULL);
    enemy_textures_attack[2] = sfTexture_createFromFile("resource/mob/attack/2.png",NULL);
    enemy_textures_attack[3] = sfTexture_createFromFile("resource/mob/attack/3.png",NULL);
    enemy_textures_attack[4] = sfTexture_createFromFile("resource/mob/attack/4.png",NULL);
    enemy_textures_attack[5] = sfTexture_createFromFile("resource/mob/attack/5.png",NULL);
    enemy_textures_attack[6] = sfTexture_createFromFile("resource/mob/attack/6.png",NULL);
    enemy_textures_attack[7] = sfTexture_createFromFile("resource/mob/attack/7.png",NULL);
    enemy_textures_attack[8] = sfTexture_createFromFile("resource/mob/attack/8.png",NULL);
    enemy_textures_attack[9] = sfTexture_createFromFile("resource/mob/attack/9.png",NULL);
    enemy_textures_attack[10] = sfTexture_createFromFile("resource/mob/attack/10.png",NULL);
    enemy_textures_attack[11] = sfTexture_createFromFile("resource/mob/attack/11.png",NULL);
    enemy_textures_attack[12] = sfTexture_createFromFile("resource/mob/attack/12.png",NULL);
    enemy_textures_attack[13] = sfTexture_createFromFile("resource/mob/attack/13.png",NULL);
    enemy_textures_attack[14] = sfTexture_createFromFile("resource/mob/attack/14.png",NULL);
    enemy_textures_attack[15] = sfTexture_createFromFile("resource/mob/attack/15.png",NULL);
    enemy_textures_attack[16] = sfTexture_createFromFile("resource/mob/attack/16.png",NULL);

    sfTexture **enemy_textures_idle= malloc(sizeof(sfTexture *)*4);
    enemy_textures_idle[0] = sfTexture_createFromFile("resource/mob/idle/0.png",NULL);
    enemy_textures_idle[1] = sfTexture_createFromFile("resource/mob/idle/1.png",NULL);
    enemy_textures_idle[2] = sfTexture_createFromFile("resource/mob/idle/2.png",NULL);
    enemy_textures_idle[3] = sfTexture_createFromFile("resource/mob/idle/3.png",NULL);

    sfTexture **enemy_textures_dead= malloc(sizeof(sfTexture *)*12);
    enemy_textures_dead[0] = sfTexture_createFromFile("resource/mob/dead/0.png",NULL);
    enemy_textures_dead[1] = sfTexture_createFromFile("resource/mob/dead/1.png",NULL);
    enemy_textures_dead[2] = sfTexture_createFromFile("resource/mob/dead/2.png",NULL);
    enemy_textures_dead[3] = sfTexture_createFromFile("resource/mob/dead/3.png",NULL);
    enemy_textures_dead[4] = sfTexture_createFromFile("resource/mob/dead/4.png",NULL);
    enemy_textures_dead[5] = sfTexture_createFromFile("resource/mob/dead/5.png",NULL);
    enemy_textures_dead[6] = sfTexture_createFromFile("resource/mob/dead/6.png",NULL);
    enemy_textures_dead[7] = sfTexture_createFromFile("resource/mob/dead/7.png",NULL);
    enemy_textures_dead[8] = sfTexture_createFromFile("resource/mob/dead/8.png",NULL);
    enemy_textures_dead[9] = sfTexture_createFromFile("resource/mob/dead/9.png",NULL);
    enemy_textures_dead[10] = sfTexture_createFromFile("resource/mob/dead/10.png",NULL);
    enemy_textures_dead[11] = sfTexture_createFromFile("resource/mob/dead/11.png",NULL);


// -----------------------------------------------------------
    bool isTabPressed = false;

    sfBool isIntersects_with_item = sfFalse;
    sfBool isIntersects_with_enemy = sfFalse;

// -----------------------------------------------------------

    sfTexture *bg_menu_t = sfTexture_createFromFile("resource/start_bg.png",NULL);
    sfSprite *bg_menu_s = sfSprite_create();
    sfSprite_setTexture(bg_menu_s,bg_menu_t,sfFalse); 

// -----------------------------------------------------------

    sfTexture *btn1_t = sfTexture_createFromFile("resource/button_exit.png",NULL);
    sfSprite *btn1_s = sfSprite_create();
    sfSprite_setTexture(btn1_s,btn1_t,sfFalse); 
    
    sfText *menu_text = sfText_create();
    sfText_setCharacterSize(menu_text, 15);

    sfText_setFont(menu_text, font);
    sfText_setColor(menu_text, sfWhite);
    sfText_setStyle(menu_text,sfTextBold);
    sfText_setString(menu_text,"Press ENTER to start a new game!");
    text_coords.x = 800;
    text_coords.y = 880;
    sfText_setPosition(menu_text, text_coords);
    int screen = 2;   // 1 - screensaver, 2 - menu, 3 - game

//-----------------------------------------------------------------------------------------------------------------------

//     sfTexture **screensaver_mas = malloc(sizeof(sfTexture *)*300);
//     	screensaver_mas[0] = sfTexture_createFromFile("resource/zastavOCHKA_000/0.jpg", NULL);
// 	screensaver_mas[1] = sfTexture_createFromFile("resource/zastavOCHKA_000/1.jpg", NULL);
//     screensaver_mas[2] = sfTexture_createFromFile("resource/zastavOCHKA_000/2.jpg", NULL);
//     screensaver_mas[3] = sfTexture_createFromFile("resource/zastavOCHKA_000/3.jpg", NULL);
//     screensaver_mas[4] = sfTexture_createFromFile("resource/zastavOCHKA_000/4.jpg", NULL);
// screensaver_mas[5] = sfTexture_createFromFile("resource/zastavOCHKA_000/5.jpg", NULL);
// screensaver_mas[6] = sfTexture_createFromFile("resource/zastavOCHKA_000/6.jpg", NULL);
// screensaver_mas[7] = sfTexture_createFromFile("resource/zastavOCHKA_000/7.jpg", NULL);
// screensaver_mas[8] = sfTexture_createFromFile("resource/zastavOCHKA_000/8.jpg", NULL);
// screensaver_mas[9] = sfTexture_createFromFile("resource/zastavOCHKA_000/9.jpg", NULL);
// screensaver_mas[10] = sfTexture_createFromFile("resource/zastavOCHKA_000/10.jpg", NULL);
// screensaver_mas[11] = sfTexture_createFromFile("resource/zastavOCHKA_000/11.jpg", NULL);
// screensaver_mas[12] = sfTexture_createFromFile("resource/zastavOCHKA_000/12.jpg", NULL);
// screensaver_mas[13] = sfTexture_createFromFile("resource/zastavOCHKA_000/13.jpg", NULL);
// screensaver_mas[14] = sfTexture_createFromFile("resource/zastavOCHKA_000/14.jpg", NULL);
// screensaver_mas[15] = sfTexture_createFromFile("resource/zastavOCHKA_000/15.jpg", NULL);
// screensaver_mas[16] = sfTexture_createFromFile("resource/zastavOCHKA_000/16.jpg", NULL);
// screensaver_mas[17] = sfTexture_createFromFile("resource/zastavOCHKA_000/17.jpg", NULL);
// screensaver_mas[18] = sfTexture_createFromFile("resource/zastavOCHKA_000/18.jpg", NULL);
// screensaver_mas[19] = sfTexture_createFromFile("resource/zastavOCHKA_000/19.jpg", NULL);
// screensaver_mas[20] = sfTexture_createFromFile("resource/zastavOCHKA_000/20.jpg", NULL);
// screensaver_mas[21] = sfTexture_createFromFile("resource/zastavOCHKA_000/21.jpg", NULL);
// screensaver_mas[22] = sfTexture_createFromFile("resource/zastavOCHKA_000/22.jpg", NULL);
// screensaver_mas[23] = sfTexture_createFromFile("resource/zastavOCHKA_000/23.jpg", NULL);
// screensaver_mas[24] = sfTexture_createFromFile("resource/zastavOCHKA_000/24.jpg", NULL);
// screensaver_mas[25] = sfTexture_createFromFile("resource/zastavOCHKA_000/25.jpg", NULL);
// screensaver_mas[26] = sfTexture_createFromFile("resource/zastavOCHKA_000/26.jpg", NULL);
// screensaver_mas[27] = sfTexture_createFromFile("resource/zastavOCHKA_000/27.jpg", NULL);
// screensaver_mas[28] = sfTexture_createFromFile("resource/zastavOCHKA_000/28.jpg", NULL);
// screensaver_mas[29] = sfTexture_createFromFile("resource/zastavOCHKA_000/29.jpg", NULL);
// screensaver_mas[30] = sfTexture_createFromFile("resource/zastavOCHKA_000/30.jpg", NULL);
// screensaver_mas[31] = sfTexture_createFromFile("resource/zastavOCHKA_000/31.jpg", NULL);
// screensaver_mas[32] = sfTexture_createFromFile("resource/zastavOCHKA_000/32.jpg", NULL);
// screensaver_mas[33] = sfTexture_createFromFile("resource/zastavOCHKA_000/33.jpg", NULL);
// screensaver_mas[34] = sfTexture_createFromFile("resource/zastavOCHKA_000/34.jpg", NULL);
// screensaver_mas[35] = sfTexture_createFromFile("resource/zastavOCHKA_000/35.jpg", NULL);
// screensaver_mas[36] = sfTexture_createFromFile("resource/zastavOCHKA_000/36.jpg", NULL);
// screensaver_mas[37] = sfTexture_createFromFile("resource/zastavOCHKA_000/37.jpg", NULL);
// screensaver_mas[38] = sfTexture_createFromFile("resource/zastavOCHKA_000/38.jpg", NULL);
// screensaver_mas[39] = sfTexture_createFromFile("resource/zastavOCHKA_000/39.jpg", NULL);
// screensaver_mas[40] = sfTexture_createFromFile("resource/zastavOCHKA_000/40.jpg", NULL);
// screensaver_mas[41] = sfTexture_createFromFile("resource/zastavOCHKA_000/41.jpg", NULL);
// screensaver_mas[42] = sfTexture_createFromFile("resource/zastavOCHKA_000/42.jpg", NULL);
// screensaver_mas[43] = sfTexture_createFromFile("resource/zastavOCHKA_000/43.jpg", NULL);
// screensaver_mas[44] = sfTexture_createFromFile("resource/zastavOCHKA_000/44.jpg", NULL);
// screensaver_mas[45] = sfTexture_createFromFile("resource/zastavOCHKA_000/45.jpg", NULL);
// screensaver_mas[46] = sfTexture_createFromFile("resource/zastavOCHKA_000/46.jpg", NULL);
// screensaver_mas[47] = sfTexture_createFromFile("resource/zastavOCHKA_000/47.jpg", NULL);
// screensaver_mas[48] = sfTexture_createFromFile("resource/zastavOCHKA_000/48.jpg", NULL);
// screensaver_mas[49] = sfTexture_createFromFile("resource/zastavOCHKA_000/49.jpg", NULL);
// screensaver_mas[50] = sfTexture_createFromFile("resource/zastavOCHKA_000/50.jpg", NULL);
// screensaver_mas[51] = sfTexture_createFromFile("resource/zastavOCHKA_000/51.jpg", NULL);
// screensaver_mas[52] = sfTexture_createFromFile("resource/zastavOCHKA_000/52.jpg", NULL);
// screensaver_mas[53] = sfTexture_createFromFile("resource/zastavOCHKA_000/53.jpg", NULL);
// screensaver_mas[54] = sfTexture_createFromFile("resource/zastavOCHKA_000/54.jpg", NULL);
// screensaver_mas[55] = sfTexture_createFromFile("resource/zastavOCHKA_000/55.jpg", NULL);
// screensaver_mas[56] = sfTexture_createFromFile("resource/zastavOCHKA_000/56.jpg", NULL);
// screensaver_mas[57] = sfTexture_createFromFile("resource/zastavOCHKA_000/57.jpg", NULL);
// screensaver_mas[58] = sfTexture_createFromFile("resource/zastavOCHKA_000/58.jpg", NULL);
// screensaver_mas[59] = sfTexture_createFromFile("resource/zastavOCHKA_000/59.jpg", NULL);
// screensaver_mas[60] = sfTexture_createFromFile("resource/zastavOCHKA_000/60.jpg", NULL);
// screensaver_mas[61] = sfTexture_createFromFile("resource/zastavOCHKA_000/61.jpg", NULL);
// screensaver_mas[62] = sfTexture_createFromFile("resource/zastavOCHKA_000/62.jpg", NULL);
// screensaver_mas[63] = sfTexture_createFromFile("resource/zastavOCHKA_000/63.jpg", NULL);
// screensaver_mas[64] = sfTexture_createFromFile("resource/zastavOCHKA_000/64.jpg", NULL);
// screensaver_mas[65] = sfTexture_createFromFile("resource/zastavOCHKA_000/65.jpg", NULL);
// screensaver_mas[66] = sfTexture_createFromFile("resource/zastavOCHKA_000/66.jpg", NULL);
// screensaver_mas[67] = sfTexture_createFromFile("resource/zastavOCHKA_000/67.jpg", NULL);
// screensaver_mas[68] = sfTexture_createFromFile("resource/zastavOCHKA_000/68.jpg", NULL);
// screensaver_mas[69] = sfTexture_createFromFile("resource/zastavOCHKA_000/69.jpg", NULL);
// screensaver_mas[70] = sfTexture_createFromFile("resource/zastavOCHKA_000/70.jpg", NULL);
// screensaver_mas[71] = sfTexture_createFromFile("resource/zastavOCHKA_000/71.jpg", NULL);
// screensaver_mas[72] = sfTexture_createFromFile("resource/zastavOCHKA_000/72.jpg", NULL);
// screensaver_mas[73] = sfTexture_createFromFile("resource/zastavOCHKA_000/73.jpg", NULL);
// screensaver_mas[74] = sfTexture_createFromFile("resource/zastavOCHKA_000/74.jpg", NULL);
// screensaver_mas[75] = sfTexture_createFromFile("resource/zastavOCHKA_000/75.jpg", NULL);
// screensaver_mas[76] = sfTexture_createFromFile("resource/zastavOCHKA_000/76.jpg", NULL);
// screensaver_mas[77] = sfTexture_createFromFile("resource/zastavOCHKA_000/77.jpg", NULL);
// screensaver_mas[78] = sfTexture_createFromFile("resource/zastavOCHKA_000/78.jpg", NULL);
// screensaver_mas[79] = sfTexture_createFromFile("resource/zastavOCHKA_000/79.jpg", NULL);
// screensaver_mas[80] = sfTexture_createFromFile("resource/zastavOCHKA_000/80.jpg", NULL);
// screensaver_mas[81] = sfTexture_createFromFile("resource/zastavOCHKA_000/81.jpg", NULL);
// screensaver_mas[82] = sfTexture_createFromFile("resource/zastavOCHKA_000/82.jpg", NULL);
// screensaver_mas[83] = sfTexture_createFromFile("resource/zastavOCHKA_000/83.jpg", NULL);
// screensaver_mas[84] = sfTexture_createFromFile("resource/zastavOCHKA_000/84.jpg", NULL);
// screensaver_mas[85] = sfTexture_createFromFile("resource/zastavOCHKA_000/85.jpg", NULL);
// screensaver_mas[86] = sfTexture_createFromFile("resource/zastavOCHKA_000/86.jpg", NULL);
// screensaver_mas[87] = sfTexture_createFromFile("resource/zastavOCHKA_000/87.jpg", NULL);
// screensaver_mas[88] = sfTexture_createFromFile("resource/zastavOCHKA_000/88.jpg", NULL);
// screensaver_mas[89] = sfTexture_createFromFile("resource/zastavOCHKA_000/89.jpg", NULL);
// screensaver_mas[90] = sfTexture_createFromFile("resource/zastavOCHKA_000/90.jpg", NULL);
// screensaver_mas[91] = sfTexture_createFromFile("resource/zastavOCHKA_000/91.jpg", NULL);
// screensaver_mas[92] = sfTexture_createFromFile("resource/zastavOCHKA_000/92.jpg", NULL);
// screensaver_mas[93] = sfTexture_createFromFile("resource/zastavOCHKA_000/93.jpg", NULL);
// screensaver_mas[94] = sfTexture_createFromFile("resource/zastavOCHKA_000/94.jpg", NULL);
// screensaver_mas[95] = sfTexture_createFromFile("resource/zastavOCHKA_000/95.jpg", NULL);
// screensaver_mas[96] = sfTexture_createFromFile("resource/zastavOCHKA_000/96.jpg", NULL);
// screensaver_mas[97] = sfTexture_createFromFile("resource/zastavOCHKA_000/97.jpg", NULL);
// screensaver_mas[98] = sfTexture_createFromFile("resource/zastavOCHKA_000/98.jpg", NULL);
// screensaver_mas[99] = sfTexture_createFromFile("resource/zastavOCHKA_000/99.jpg", NULL);
// screensaver_mas[100] = sfTexture_createFromFile("resource/zastavOCHKA_000/100.jpg", NULL);
// screensaver_mas[101] = sfTexture_createFromFile("resource/zastavOCHKA_000/101.jpg", NULL);
// screensaver_mas[102] = sfTexture_createFromFile("resource/zastavOCHKA_000/102.jpg", NULL);
// screensaver_mas[103] = sfTexture_createFromFile("resource/zastavOCHKA_000/103.jpg", NULL);
// screensaver_mas[104] = sfTexture_createFromFile("resource/zastavOCHKA_000/104.jpg", NULL);
// screensaver_mas[105] = sfTexture_createFromFile("resource/zastavOCHKA_000/105.jpg", NULL);
// screensaver_mas[106] = sfTexture_createFromFile("resource/zastavOCHKA_000/106.jpg", NULL);
// screensaver_mas[107] = sfTexture_createFromFile("resource/zastavOCHKA_000/107.jpg", NULL);
// screensaver_mas[108] = sfTexture_createFromFile("resource/zastavOCHKA_000/108.jpg", NULL);
// screensaver_mas[109] = sfTexture_createFromFile("resource/zastavOCHKA_000/109.jpg", NULL);
// screensaver_mas[110] = sfTexture_createFromFile("resource/zastavOCHKA_000/110.jpg", NULL);
// screensaver_mas[111] = sfTexture_createFromFile("resource/zastavOCHKA_000/111.jpg", NULL);
// screensaver_mas[112] = sfTexture_createFromFile("resource/zastavOCHKA_000/112.jpg", NULL);
// screensaver_mas[113] = sfTexture_createFromFile("resource/zastavOCHKA_000/113.jpg", NULL);
// screensaver_mas[114] = sfTexture_createFromFile("resource/zastavOCHKA_000/114.jpg", NULL);
// screensaver_mas[115] = sfTexture_createFromFile("resource/zastavOCHKA_000/115.jpg", NULL);
// screensaver_mas[116] = sfTexture_createFromFile("resource/zastavOCHKA_000/116.jpg", NULL);
// screensaver_mas[117] = sfTexture_createFromFile("resource/zastavOCHKA_000/117.jpg", NULL);
// screensaver_mas[118] = sfTexture_createFromFile("resource/zastavOCHKA_000/118.jpg", NULL);
// screensaver_mas[119] = sfTexture_createFromFile("resource/zastavOCHKA_000/119.jpg", NULL);
// screensaver_mas[120] = sfTexture_createFromFile("resource/zastavOCHKA_000/120.jpg", NULL);
// screensaver_mas[121] = sfTexture_createFromFile("resource/zastavOCHKA_000/121.jpg", NULL);
// screensaver_mas[122] = sfTexture_createFromFile("resource/zastavOCHKA_000/122.jpg", NULL);
// screensaver_mas[123] = sfTexture_createFromFile("resource/zastavOCHKA_000/123.jpg", NULL);
// screensaver_mas[124] = sfTexture_createFromFile("resource/zastavOCHKA_000/124.jpg", NULL);
// screensaver_mas[125] = sfTexture_createFromFile("resource/zastavOCHKA_000/125.jpg", NULL);
// screensaver_mas[126] = sfTexture_createFromFile("resource/zastavOCHKA_000/126.jpg", NULL);
// screensaver_mas[127] = sfTexture_createFromFile("resource/zastavOCHKA_000/127.jpg", NULL);
// screensaver_mas[128] = sfTexture_createFromFile("resource/zastavOCHKA_000/128.jpg", NULL);
// screensaver_mas[129] = sfTexture_createFromFile("resource/zastavOCHKA_000/129.jpg", NULL);
// screensaver_mas[130] = sfTexture_createFromFile("resource/zastavOCHKA_000/130.jpg", NULL);
// screensaver_mas[131] = sfTexture_createFromFile("resource/zastavOCHKA_000/131.jpg", NULL);
// screensaver_mas[132] = sfTexture_createFromFile("resource/zastavOCHKA_000/132.jpg", NULL);
// screensaver_mas[133] = sfTexture_createFromFile("resource/zastavOCHKA_000/133.jpg", NULL);
// screensaver_mas[134] = sfTexture_createFromFile("resource/zastavOCHKA_000/134.jpg", NULL);
// screensaver_mas[135] = sfTexture_createFromFile("resource/zastavOCHKA_000/135.jpg", NULL);
// screensaver_mas[136] = sfTexture_createFromFile("resource/zastavOCHKA_000/136.jpg", NULL);
// screensaver_mas[137] = sfTexture_createFromFile("resource/zastavOCHKA_000/137.jpg", NULL);
// screensaver_mas[138] = sfTexture_createFromFile("resource/zastavOCHKA_000/138.jpg", NULL);
// screensaver_mas[139] = sfTexture_createFromFile("resource/zastavOCHKA_000/139.jpg", NULL);
// screensaver_mas[140] = sfTexture_createFromFile("resource/zastavOCHKA_000/140.jpg", NULL);
// screensaver_mas[141] = sfTexture_createFromFile("resource/zastavOCHKA_000/141.jpg", NULL);
// screensaver_mas[142] = sfTexture_createFromFile("resource/zastavOCHKA_000/142.jpg", NULL);
// screensaver_mas[143] = sfTexture_createFromFile("resource/zastavOCHKA_000/143.jpg", NULL);
// screensaver_mas[144] = sfTexture_createFromFile("resource/zastavOCHKA_000/144.jpg", NULL);
// screensaver_mas[145] = sfTexture_createFromFile("resource/zastavOCHKA_000/145.jpg", NULL);
// screensaver_mas[146] = sfTexture_createFromFile("resource/zastavOCHKA_000/146.jpg", NULL);
// screensaver_mas[147] = sfTexture_createFromFile("resource/zastavOCHKA_000/147.jpg", NULL);
// screensaver_mas[148] = sfTexture_createFromFile("resource/zastavOCHKA_000/148.jpg", NULL);
// screensaver_mas[149] = sfTexture_createFromFile("resource/zastavOCHKA_000/149.jpg", NULL);
// screensaver_mas[150] = sfTexture_createFromFile("resource/zastavOCHKA_000/150.jpg", NULL);
// screensaver_mas[151] = sfTexture_createFromFile("resource/zastavOCHKA_000/151.jpg", NULL);
// screensaver_mas[152] = sfTexture_createFromFile("resource/zastavOCHKA_000/152.jpg", NULL);
// screensaver_mas[153] = sfTexture_createFromFile("resource/zastavOCHKA_000/153.jpg", NULL);
// screensaver_mas[154] = sfTexture_createFromFile("resource/zastavOCHKA_000/154.jpg", NULL);
// screensaver_mas[155] = sfTexture_createFromFile("resource/zastavOCHKA_000/155.jpg", NULL);
// screensaver_mas[156] = sfTexture_createFromFile("resource/zastavOCHKA_000/156.jpg", NULL);
// screensaver_mas[157] = sfTexture_createFromFile("resource/zastavOCHKA_000/157.jpg", NULL);
// screensaver_mas[158] = sfTexture_createFromFile("resource/zastavOCHKA_000/158.jpg", NULL);
// screensaver_mas[159] = sfTexture_createFromFile("resource/zastavOCHKA_000/159.jpg", NULL);
// screensaver_mas[160] = sfTexture_createFromFile("resource/zastavOCHKA_000/160.jpg", NULL);
// screensaver_mas[161] = sfTexture_createFromFile("resource/zastavOCHKA_000/161.jpg", NULL);
// screensaver_mas[162] = sfTexture_createFromFile("resource/zastavOCHKA_000/162.jpg", NULL);
// screensaver_mas[163] = sfTexture_createFromFile("resource/zastavOCHKA_000/163.jpg", NULL);
// screensaver_mas[164] = sfTexture_createFromFile("resource/zastavOCHKA_000/164.jpg", NULL);
// screensaver_mas[165] = sfTexture_createFromFile("resource/zastavOCHKA_000/165.jpg", NULL);
// screensaver_mas[166] = sfTexture_createFromFile("resource/zastavOCHKA_000/166.jpg", NULL);
// screensaver_mas[167] = sfTexture_createFromFile("resource/zastavOCHKA_000/167.jpg", NULL);
// screensaver_mas[168] = sfTexture_createFromFile("resource/zastavOCHKA_000/168.jpg", NULL);
// screensaver_mas[169] = sfTexture_createFromFile("resource/zastavOCHKA_000/169.jpg", NULL);
// screensaver_mas[170] = sfTexture_createFromFile("resource/zastavOCHKA_000/170.jpg", NULL);
// screensaver_mas[171] = sfTexture_createFromFile("resource/zastavOCHKA_000/171.jpg", NULL);
// screensaver_mas[172] = sfTexture_createFromFile("resource/zastavOCHKA_000/172.jpg", NULL);
// screensaver_mas[173] = sfTexture_createFromFile("resource/zastavOCHKA_000/173.jpg", NULL);
// screensaver_mas[174] = sfTexture_createFromFile("resource/zastavOCHKA_000/174.jpg", NULL);
// screensaver_mas[175] = sfTexture_createFromFile("resource/zastavOCHKA_000/175.jpg", NULL);
// screensaver_mas[176] = sfTexture_createFromFile("resource/zastavOCHKA_000/176.jpg", NULL);
// screensaver_mas[177] = sfTexture_createFromFile("resource/zastavOCHKA_000/177.jpg", NULL);
// screensaver_mas[178] = sfTexture_createFromFile("resource/zastavOCHKA_000/178.jpg", NULL);
// screensaver_mas[179] = sfTexture_createFromFile("resource/zastavOCHKA_000/179.jpg", NULL);
// screensaver_mas[180] = sfTexture_createFromFile("resource/zastavOCHKA_000/180.jpg", NULL);
// screensaver_mas[181] = sfTexture_createFromFile("resource/zastavOCHKA_000/181.jpg", NULL);
// screensaver_mas[182] = sfTexture_createFromFile("resource/zastavOCHKA_000/182.jpg", NULL);
// screensaver_mas[183] = sfTexture_createFromFile("resource/zastavOCHKA_000/183.jpg", NULL);
// screensaver_mas[184] = sfTexture_createFromFile("resource/zastavOCHKA_000/184.jpg", NULL);
// screensaver_mas[185] = sfTexture_createFromFile("resource/zastavOCHKA_000/185.jpg", NULL);
// screensaver_mas[186] = sfTexture_createFromFile("resource/zastavOCHKA_000/186.jpg", NULL);
// screensaver_mas[187] = sfTexture_createFromFile("resource/zastavOCHKA_000/187.jpg", NULL);
// screensaver_mas[188] = sfTexture_createFromFile("resource/zastavOCHKA_000/188.jpg", NULL);
// screensaver_mas[189] = sfTexture_createFromFile("resource/zastavOCHKA_000/189.jpg", NULL);
// screensaver_mas[190] = sfTexture_createFromFile("resource/zastavOCHKA_000/190.jpg", NULL);
// screensaver_mas[191] = sfTexture_createFromFile("resource/zastavOCHKA_000/191.jpg", NULL);
// screensaver_mas[192] = sfTexture_createFromFile("resource/zastavOCHKA_000/192.jpg", NULL);
// screensaver_mas[193] = sfTexture_createFromFile("resource/zastavOCHKA_000/193.jpg", NULL);
// screensaver_mas[194] = sfTexture_createFromFile("resource/zastavOCHKA_000/194.jpg", NULL);
// screensaver_mas[195] = sfTexture_createFromFile("resource/zastavOCHKA_000/195.jpg", NULL);
// screensaver_mas[196] = sfTexture_createFromFile("resource/zastavOCHKA_000/196.jpg", NULL);
// screensaver_mas[197] = sfTexture_createFromFile("resource/zastavOCHKA_000/197.jpg", NULL);
// screensaver_mas[198] = sfTexture_createFromFile("resource/zastavOCHKA_000/198.jpg", NULL);
// screensaver_mas[199] = sfTexture_createFromFile("resource/zastavOCHKA_000/199.jpg", NULL);
// screensaver_mas[200] = sfTexture_createFromFile("resource/zastavOCHKA_000/200.jpg", NULL);
// screensaver_mas[201] = sfTexture_createFromFile("resource/zastavOCHKA_000/201.jpg", NULL);
// screensaver_mas[202] = sfTexture_createFromFile("resource/zastavOCHKA_000/202.jpg", NULL);
// screensaver_mas[203] = sfTexture_createFromFile("resource/zastavOCHKA_000/203.jpg", NULL);
// screensaver_mas[204] = sfTexture_createFromFile("resource/zastavOCHKA_000/204.jpg", NULL);
// screensaver_mas[205] = sfTexture_createFromFile("resource/zastavOCHKA_000/205.jpg", NULL);
// screensaver_mas[206] = sfTexture_createFromFile("resource/zastavOCHKA_000/206.jpg", NULL);
// screensaver_mas[207] = sfTexture_createFromFile("resource/zastavOCHKA_000/207.jpg", NULL);
// screensaver_mas[208] = sfTexture_createFromFile("resource/zastavOCHKA_000/208.jpg", NULL);
// screensaver_mas[209] = sfTexture_createFromFile("resource/zastavOCHKA_000/209.jpg", NULL);
// screensaver_mas[210] = sfTexture_createFromFile("resource/zastavOCHKA_000/210.jpg", NULL);
// screensaver_mas[211] = sfTexture_createFromFile("resource/zastavOCHKA_000/211.jpg", NULL);
// screensaver_mas[212] = sfTexture_createFromFile("resource/zastavOCHKA_000/212.jpg", NULL);
// screensaver_mas[213] = sfTexture_createFromFile("resource/zastavOCHKA_000/213.jpg", NULL);
// screensaver_mas[214] = sfTexture_createFromFile("resource/zastavOCHKA_000/214.jpg", NULL);
// screensaver_mas[215] = sfTexture_createFromFile("resource/zastavOCHKA_000/215.jpg", NULL);
// screensaver_mas[216] = sfTexture_createFromFile("resource/zastavOCHKA_000/216.jpg", NULL);
// screensaver_mas[217] = sfTexture_createFromFile("resource/zastavOCHKA_000/217.jpg", NULL);
// screensaver_mas[218] = sfTexture_createFromFile("resource/zastavOCHKA_000/218.jpg", NULL);
// screensaver_mas[219] = sfTexture_createFromFile("resource/zastavOCHKA_000/219.jpg", NULL);
// screensaver_mas[220] = sfTexture_createFromFile("resource/zastavOCHKA_000/220.jpg", NULL);
// screensaver_mas[221] = sfTexture_createFromFile("resource/zastavOCHKA_000/221.jpg", NULL);
// screensaver_mas[222] = sfTexture_createFromFile("resource/zastavOCHKA_000/222.jpg", NULL);
// screensaver_mas[223] = sfTexture_createFromFile("resource/zastavOCHKA_000/223.jpg", NULL);
// screensaver_mas[224] = sfTexture_createFromFile("resource/zastavOCHKA_000/224.jpg", NULL);
// screensaver_mas[225] = sfTexture_createFromFile("resource/zastavOCHKA_000/225.jpg", NULL);
// screensaver_mas[226] = sfTexture_createFromFile("resource/zastavOCHKA_000/226.jpg", NULL);
// screensaver_mas[227] = sfTexture_createFromFile("resource/zastavOCHKA_000/227.jpg", NULL);
// screensaver_mas[228] = sfTexture_createFromFile("resource/zastavOCHKA_000/228.jpg", NULL);
// screensaver_mas[229] = sfTexture_createFromFile("resource/zastavOCHKA_000/229.jpg", NULL);
// screensaver_mas[230] = sfTexture_createFromFile("resource/zastavOCHKA_000/230.jpg", NULL);
// screensaver_mas[231] = sfTexture_createFromFile("resource/zastavOCHKA_000/231.jpg", NULL);
// screensaver_mas[232] = sfTexture_createFromFile("resource/zastavOCHKA_000/232.jpg", NULL);
// screensaver_mas[233] = sfTexture_createFromFile("resource/zastavOCHKA_000/233.jpg", NULL);
// screensaver_mas[234] = sfTexture_createFromFile("resource/zastavOCHKA_000/234.jpg", NULL);
// screensaver_mas[235] = sfTexture_createFromFile("resource/zastavOCHKA_000/235.jpg", NULL);
// screensaver_mas[236] = sfTexture_createFromFile("resource/zastavOCHKA_000/236.jpg", NULL);
// screensaver_mas[237] = sfTexture_createFromFile("resource/zastavOCHKA_000/237.jpg", NULL);
// screensaver_mas[238] = sfTexture_createFromFile("resource/zastavOCHKA_000/238.jpg", NULL);
// screensaver_mas[239] = sfTexture_createFromFile("resource/zastavOCHKA_000/239.jpg", NULL);
// screensaver_mas[240] = sfTexture_createFromFile("resource/zastavOCHKA_000/240.jpg", NULL);
// screensaver_mas[241] = sfTexture_createFromFile("resource/zastavOCHKA_000/241.jpg", NULL);
// screensaver_mas[242] = sfTexture_createFromFile("resource/zastavOCHKA_000/242.jpg", NULL);
// screensaver_mas[243] = sfTexture_createFromFile("resource/zastavOCHKA_000/243.jpg", NULL);
// screensaver_mas[244] = sfTexture_createFromFile("resource/zastavOCHKA_000/244.jpg", NULL);
// screensaver_mas[245] = sfTexture_createFromFile("resource/zastavOCHKA_000/245.jpg", NULL);
// screensaver_mas[246] = sfTexture_createFromFile("resource/zastavOCHKA_000/246.jpg", NULL);
// screensaver_mas[247] = sfTexture_createFromFile("resource/zastavOCHKA_000/247.jpg", NULL);
// screensaver_mas[248] = sfTexture_createFromFile("resource/zastavOCHKA_000/248.jpg", NULL);
// screensaver_mas[249] = sfTexture_createFromFile("resource/zastavOCHKA_000/249.jpg", NULL);
// screensaver_mas[250] = sfTexture_createFromFile("resource/zastavOCHKA_000/250.jpg", NULL);
// screensaver_mas[251] = sfTexture_createFromFile("resource/zastavOCHKA_000/251.jpg", NULL);
// screensaver_mas[252] = sfTexture_createFromFile("resource/zastavOCHKA_000/252.jpg", NULL);
// screensaver_mas[253] = sfTexture_createFromFile("resource/zastavOCHKA_000/253.jpg", NULL);
// screensaver_mas[254] = sfTexture_createFromFile("resource/zastavOCHKA_000/254.jpg", NULL);
// screensaver_mas[255] = sfTexture_createFromFile("resource/zastavOCHKA_000/255.jpg", NULL);
// screensaver_mas[256] = sfTexture_createFromFile("resource/zastavOCHKA_000/256.jpg", NULL);
// screensaver_mas[257] = sfTexture_createFromFile("resource/zastavOCHKA_000/257.jpg", NULL);
// screensaver_mas[258] = sfTexture_createFromFile("resource/zastavOCHKA_000/258.jpg", NULL);
// screensaver_mas[259] = sfTexture_createFromFile("resource/zastavOCHKA_000/259.jpg", NULL);
// screensaver_mas[260] = sfTexture_createFromFile("resource/zastavOCHKA_000/260.jpg", NULL);
// screensaver_mas[261] = sfTexture_createFromFile("resource/zastavOCHKA_000/261.jpg", NULL);
// screensaver_mas[262] = sfTexture_createFromFile("resource/zastavOCHKA_000/262.jpg", NULL);
// screensaver_mas[263] = sfTexture_createFromFile("resource/zastavOCHKA_000/263.jpg", NULL);
// screensaver_mas[264] = sfTexture_createFromFile("resource/zastavOCHKA_000/264.jpg", NULL);
// screensaver_mas[265] = sfTexture_createFromFile("resource/zastavOCHKA_000/265.jpg", NULL);
// screensaver_mas[266] = sfTexture_createFromFile("resource/zastavOCHKA_000/266.jpg", NULL);
// screensaver_mas[267] = sfTexture_createFromFile("resource/zastavOCHKA_000/267.jpg", NULL);
// screensaver_mas[268] = sfTexture_createFromFile("resource/zastavOCHKA_000/268.jpg", NULL);
// screensaver_mas[269] = sfTexture_createFromFile("resource/zastavOCHKA_000/269.jpg", NULL);
// screensaver_mas[270] = sfTexture_createFromFile("resource/zastavOCHKA_000/270.jpg", NULL);
// screensaver_mas[271] = sfTexture_createFromFile("resource/zastavOCHKA_000/271.jpg", NULL);
// screensaver_mas[272] = sfTexture_createFromFile("resource/zastavOCHKA_000/272.jpg", NULL);
// screensaver_mas[273] = sfTexture_createFromFile("resource/zastavOCHKA_000/273.jpg", NULL);
// screensaver_mas[274] = sfTexture_createFromFile("resource/zastavOCHKA_000/274.jpg", NULL);
// screensaver_mas[275] = sfTexture_createFromFile("resource/zastavOCHKA_000/275.jpg", NULL);
// screensaver_mas[276] = sfTexture_createFromFile("resource/zastavOCHKA_000/276.jpg", NULL);
// screensaver_mas[277] = sfTexture_createFromFile("resource/zastavOCHKA_000/277.jpg", NULL);
// screensaver_mas[278] = sfTexture_createFromFile("resource/zastavOCHKA_000/278.jpg", NULL);
// screensaver_mas[279] = sfTexture_createFromFile("resource/zastavOCHKA_000/279.jpg", NULL);
// screensaver_mas[280] = sfTexture_createFromFile("resource/zastavOCHKA_000/280.jpg", NULL);
// screensaver_mas[281] = sfTexture_createFromFile("resource/zastavOCHKA_000/281.jpg", NULL);
// screensaver_mas[282] = sfTexture_createFromFile("resource/zastavOCHKA_000/282.jpg", NULL);
// screensaver_mas[283] = sfTexture_createFromFile("resource/zastavOCHKA_000/283.jpg", NULL);
// screensaver_mas[284] = sfTexture_createFromFile("resource/zastavOCHKA_000/284.jpg", NULL);
// screensaver_mas[285] = sfTexture_createFromFile("resource/zastavOCHKA_000/285.jpg", NULL);
// screensaver_mas[286] = sfTexture_createFromFile("resource/zastavOCHKA_000/286.jpg", NULL);
// screensaver_mas[287] = sfTexture_createFromFile("resource/zastavOCHKA_000/287.jpg", NULL);
// screensaver_mas[288] = sfTexture_createFromFile("resource/zastavOCHKA_000/288.jpg", NULL);
// screensaver_mas[289] = sfTexture_createFromFile("resource/zastavOCHKA_000/289.jpg", NULL);
// screensaver_mas[290] = sfTexture_createFromFile("resource/zastavOCHKA_000/290.jpg", NULL);
// screensaver_mas[291] = sfTexture_createFromFile("resource/zastavOCHKA_000/291.jpg", NULL);
// screensaver_mas[292] = sfTexture_createFromFile("resource/zastavOCHKA_000/292.jpg", NULL);
// screensaver_mas[293] = sfTexture_createFromFile("resource/zastavOCHKA_000/293.jpg", NULL);
// screensaver_mas[294] = sfTexture_createFromFile("resource/zastavOCHKA_000/294.jpg", NULL);
// screensaver_mas[295] = sfTexture_createFromFile("resource/zastavOCHKA_000/295.jpg", NULL);
// screensaver_mas[296] = sfTexture_createFromFile("resource/zastavOCHKA_000/296.jpg", NULL);
// screensaver_mas[297] = sfTexture_createFromFile("resource/zastavOCHKA_000/297.jpg", NULL);
// screensaver_mas[298] = sfTexture_createFromFile("resource/zastavOCHKA_000/298.jpg", NULL);
// screensaver_mas[299] = sfTexture_createFromFile("resource/zastavOCHKA_000/299.jpg", NULL);	
//     float cur_frame_sc = 0;
//     sfSprite *screensaver_s = sfSprite_create();
//     sfVector2f posit;
//     posit.x = 0;
//     posit.y = 0;
//     sfSprite_setPosition(screensaver_s, posit);
    

// START OF GAME ------------------------------------------------------------------------------------------
    while(sfRenderWindow_isOpen(main_window)){
        sfTime stime = sfClock_getElapsedTime(clock);
        sfClock_restart(clock);
        time = stime.microseconds/1000;
        sfEvent event;
        switch (screen)
        {
        case 1:
            // while(sfRenderWindow_pollEvent(main_window, &event)){
            //     if(event.type == sfEvtClosed)
            //     {
            //         sfRenderWindow_close(main_window);
            //     }
            //     if(event.type == sfEvtKeyPressed){
            //         if(event.key.code == sfKeyE){
            //             screen = 2;
            //         }
            //         if(event.key.code == sfKeyQ)
            //             exit(0);
            //     }
            //     // printf("%s","abc");
            //     cur_frame_sc +=0.05*time;
            //     if(cur_frame_sc > 299){
            //         screen = 2;
            //     }else {
            //         // cur_frame_sc = cur_frame_sc+1;
            //         sfSprite_setTexture(screensaver_s, screensaver_mas[(int)cur_frame_sc], sfTrue);
            //     }
            // }
            // sfRenderWindow_drawSprite(main_window, screensaver_s, NULL);            
            break;
        
        case 2:
            while(sfRenderWindow_pollEvent(main_window, &event)){
                if(event.type == sfEvtClosed)
                {
                    sfRenderWindow_close(main_window);
                }
                if(event.type == sfEvtKeyPressed){
                    if(event.key.code == sfKeyEnter){
                        screen = 3;
                    }
                    if(event.key.code == sfKeyQ)
                        exit(0);
                }
            }
        sfRenderWindow_drawSprite(main_window, bg_menu_s, NULL);
        sfRenderWindow_drawText(main_window,menu_text, NULL);

            break;
        case 3:
      if(isMap1Active){
            cur_frame_npc += 0.005*time;
            if(cur_frame_npc > 6){
                cur_frame_npc -= 6;
                sfSprite_setTexture(NPC.Sprite, npc_texture_mas_idle[(int)cur_frame_npc], sfTrue);
            }
                else
                    sfSprite_setTexture(NPC.Sprite, npc_texture_mas_idle[(int)cur_frame_npc], sfTrue);
            
            sfIntRect char_rect = sfSprite_getTextureRect(Character.Sprite);
            sfIntRect npc_rect = sfSprite_getTextureRect(NPC.Sprite);
            sfIntRect inter;
            char_rect.left = Character.dx;
            char_rect.top = Character.dy;
            npc_rect.top = NPC.dy;
            npc_rect.left = NPC.dx;
            isIntersects_with_npc = sfIntRect_intersects(&char_rect, &npc_rect, NULL);
            
        }
        if(Character.dx > 1920){
            isMap1Active = false;
            Character.dx = 0;
            character_coords.x = Character.dx;
            character_coords.y = Character.dy;
            sfSprite_setPosition(Character.Sprite, character_coords);
        }
        if(Character.dx < 0){
            isMap1Active = true;
            Character.dx = 1800;
            character_coords.x = Character.dx;
            character_coords.y = Character.dy;
            sfSprite_setPosition(Character.Sprite, character_coords);
        }

        if(!isMap1Active && !quest_1.isComplete){
            // printf("%s","abcd");
            sfIntRect char_rect = sfSprite_getTextureRect(Character.Sprite);
            sfIntRect item_rect = sfSprite_getTextureRect(item_for_quest_s);
            char_rect.left = Character.dx;
            char_rect.top = Character.dy;
            item_rect.top = item_pos.y;
            item_rect.left = item_pos.x;
            isIntersects_with_item = sfIntRect_intersects(&char_rect, &item_rect, NULL);
            if(isIntersects_with_item == sfTrue){
                // printf("%s","abc");
                quest_1.isComplete = true;
            }            
        }

        if(!isMap1Active && !quest_2.isComplete){
            sfIntRect char_rect = sfSprite_getTextureRect(Character.Sprite);
            sfIntRect enemy_rect = sfSprite_getTextureRect(Enemy.Sprite);
            char_rect.left = Character.dx;
            char_rect.top = Character.dy;
            enemy_rect.top = enemy_coords.y;
            enemy_rect.left = enemy_coords.x;
            isIntersects_with_enemy = sfIntRect_intersects(&char_rect, &enemy_rect, NULL);
        }
            // printf("%s", "Character hp=");
            // printf("%f", Character.hp);
            // printf("%s", "\nEnemy hp=");
            // printf("%f", Enemy.hp);
            // printf("%c",'\n');

        if(!isIntersects_with_enemy && Enemy.isDead == false){
                cur_frame_enemy += 0.007*time;
                if(cur_frame_enemy > 3){
                    cur_frame_enemy -= 3;
                    sfSprite_setTexture(Enemy.Sprite, enemy_textures_idle[(int)cur_frame_enemy], sfTrue);                    
                } else {
                    sfSprite_setTexture(Enemy.Sprite, enemy_textures_idle[(int)cur_frame_enemy], sfTrue);
                }
        }
        if(Enemy.hp <= 0){
            Enemy.isDead = true;
            quest_2.isComplete = true;
            sfSprite_setTexture(Enemy.Sprite, enemy_textures_dead[11], sfTrue);                
        }
        if(isIntersects_with_enemy && Enemy.isDead == false){
                cur_frame_enemy +=0.006*time;
                
                if(Enemy.hp <= 10){
                    if(cur_frame_enemy > 11){
                        Enemy.hp = 0;
                        quest_2.isComplete = true;
                        cur_frame_enemy -= 11;
                        sfSprite_setTexture(Enemy.Sprite, enemy_textures_dead[(int)cur_frame_enemy], sfTrue);                    
                }
                else {
                    sfSprite_setTexture(Enemy.Sprite, enemy_textures_dead[(int)cur_frame_enemy], sfTrue);

                    }
                } else {
                if(cur_frame_enemy > 16){
                    cur_frame_enemy -= 16;
                    Character.hp = Character.hp - 0.1;
                    sfSprite_setTexture(Enemy.Sprite, enemy_textures_attack[(int)cur_frame_enemy], sfTrue);                    
                }
                else {
                    Character.hp = Character.hp - 0.1;
                    sfSprite_setTexture(Enemy.Sprite, enemy_textures_attack[(int)cur_frame_enemy], sfTrue);

                }                    
                }


                if(sfKeyboard_isKeyPressed(sfKeyF) && !sfKeyboard_isKeyPressed(sfKeyLControl) && Character.onGround){
                current_frame += 0.008*time;
                
                if(current_frame > 11){
                    current_frame -= 11;
                    sfSprite_setTexture(Character.Sprite, character_texture_mas_attack[(int)current_frame], sfTrue);                    
                }
                else {
                    sfSprite_setTexture(Character.Sprite, character_texture_mas_attack[(int)current_frame], sfTrue);

                }
                Enemy.hp = Enemy.hp - 0.2;

                }
        }

        if(isIntersects_with_npc && quest_1.isActive == false){
            quest_1.isActive = true;
            if(quest_1.isComplete){
                quest_1.isActive = false;
            }
        }
        if(isIntersects_with_npc && quest_1.isComplete){
            Character.hp = 100.0;
            quest_2.isActive = true;
            if(quest_2.isComplete){
                quest_2.isActive = false;
            }
        }
        


        if(!Character.onGround){
            // offset.y = 0;
            if(sfKeyboard_isKeyPressed(sfKeyD))
                offset.x = 0.3 * time;
            if(sfKeyboard_isKeyPressed(sfKeyA))
                offset.x = -0.3 * time;
            Character.onGround = false;
            offset.y = offset.y +0.018 *time;
            Character.dy = Character.dy + offset.y;
            // offset.x = 0;
            if(Character.dy > (float)ground){
                // Character.dy = ground + 50;
                // offset.y = 0;
                Character.onGround = true;
                Character.dx = Character.dx + offset.x;
                sfSprite_move(Character.Sprite, offset); 
            } else{
                Character.dx = Character.dx + offset.x;
                sfSprite_move(Character.Sprite, offset); 
            }
              
        }

        
        while(sfRenderWindow_pollEvent(main_window, &event)){
            if(event.type == sfEvtClosed)
            {
                sfRenderWindow_close(main_window);
            }
            if(event.type == sfEvtKeyPressed){
                if(event.key.code == sfKeyTab){
                    if(isTabPressed == false){
                        isTabPressed = true;
                    } else {
                        isTabPressed = false;
                    }
                }

        }/*----------------------------------------------------------------------------------------------------*/
    

 

        }/*----------------------------------------------------------------------------------------------------*/
        

        if(sfKeyboard_isKeyPressed(sfKeyF) && !sfKeyboard_isKeyPressed(sfKeyLControl) && Character.onGround){
                
                current_frame += 0.009*time;
                if(current_frame > 12){
                    current_frame -= 12;
                    sfSprite_setTexture(Character.Sprite, character_texture_mas_attack[(int)current_frame], sfTrue);                    
                }
                else {
                    sfSprite_setTexture(Character.Sprite, character_texture_mas_attack[(int)current_frame], sfTrue);
                    // offset.x = 0;
                    // offset.y = 0;
                    // sfSprite_move(Character.Sprite, offset);
                } 
        }


         if(sfKeyboard_isKeyPressed(sfKeyD) && !sfKeyboard_isKeyPressed(sfKeyLControl) && Character.onGround){           //право
             current_frame += 0.008*time;
            if(current_frame > 7){
                current_frame -= 7;
                sfSprite_setTexture(Character.Sprite, character_texture_mas_r[(int)current_frame], sfTrue);
            }
            else 
                sfSprite_setTexture(Character.Sprite, character_texture_mas_r[(int)current_frame], sfTrue);
            if(sfKeyboard_isKeyPressed(sfKeySpace) && Character.onGround){                //прыжок вправо
                offset.y = -0.5 * time;
                Character.dy = Character.dy + offset.y;
                Character.onGround = false;
            } else {
                offset.x = 0.2 * time;
                offset.y = 0;
            }
            
            Character.dx = Character.dx + offset.x;
            sfSprite_move(Character.Sprite, offset);
        }/*----------------------------------------------------------------------------------------------------*/
             if(sfKeyboard_isKeyPressed(sfKeyA) && !sfKeyboard_isKeyPressed(sfKeyLControl) && Character.onGround){           //лево
             current_frame += 0.008*time;
            if(current_frame > 7){
                current_frame -= 7;
                sfSprite_setTexture(Character.Sprite, character_texture_mas_l[(int)current_frame], sfTrue);
            }
                
            else 
                sfSprite_setTexture(Character.Sprite, character_texture_mas_l[(int)current_frame], sfTrue);
        if(sfKeyboard_isKeyPressed(sfKeySpace) && Character.onGround){                //прыжок влево
                offset.y = -0.5 * time;
                Character.dy = Character.dy + offset.y;
                Character.onGround = false;

        } else {
            offset.x = -0.2 * time;
            offset.y = 0;
        }
            Character.dx = Character.dx + offset.x;
            sfSprite_move(Character.Sprite, offset);
        }/*----------------------------------------------------------------------------------------------------*/
        
            if(sfKeyboard_isKeyPressed(sfKeySpace) && !sfKeyboard_isKeyPressed(sfKeyLControl) && Character.onGround){                //прыжок на месте
            current_frame += 0.007*time;
            if(current_frame > 6){
                current_frame -= 6;
                sfSprite_setTexture(Character.Sprite, character_texture_mas_jump[(int)current_frame], sfTrue);
            }
                
                else
                    sfSprite_setTexture(Character.Sprite, character_texture_mas_jump[(int)current_frame], sfTrue);
            if(Character.onGround){
                offset.y = -6 ;
                Character.dy = Character.dy + offset.y;
                Character.onGround = false;
                offset.x = 0;
            }

            // UpdateCharacter(Character, time, ground, &offset);
            sfSprite_move(Character.Sprite, offset);
        }/*----------------------------------------------------------------------------------------------------*/

        
        if(sfKeyboard_isKeyPressed(sfKeyLControl)){                //присел 
            current_frame += 0.005*time;
            if(current_frame > 4){
                current_frame -= 4;
                sfSprite_setTexture(Character.Sprite, character_texture_mas_crouch[(int)current_frame], sfTrue);
            }
                
                else
                    sfSprite_setTexture(Character.Sprite, character_texture_mas_crouch[(int)current_frame], sfTrue);
            // offset.x = 0;
            // offset.y = 0;
            // sfSprite_move(Character.Sprite, offset);
        }/*----------------------------------------------------------------------------------------------------*/
        
        if(!sfKeyboard_isKeyPressed(sfKeyF) && !sfKeyboard_isKeyPressed(sfKeySpace) && !sfKeyboard_isKeyPressed(sfKeyLControl) && !sfKeyboard_isKeyPressed(sfKeyA) && !sfKeyboard_isKeyPressed(sfKeyD)){
            current_frame += 0.007*time;
            if(current_frame > 5){
                current_frame -= 5;
                sfSprite_setTexture(Character.Sprite, character_texture_mas_afk[(int)current_frame], sfTrue);
            }
            else 
                sfSprite_setTexture(Character.Sprite, character_texture_mas_afk[(int)current_frame], sfTrue);
            // offset.x = 0;
            // offset.y = 0;
            // sfSprite_move(Character.Sprite, offset);
        }
        
        sfRenderWindow_clear(main_window,sfBlack);
        
        if(isMap1Active){
            sfRenderWindow_drawSprite(main_window,background_s1,NULL);
            sfRenderWindow_drawSprite(main_window,NPC.Sprite,NULL);
        } else {
            sfRenderWindow_drawSprite(main_window,background_s2,NULL);
            if(quest_1.isComplete == false)
                sfRenderWindow_drawSprite(main_window,item_for_quest_s,NULL);
            else if(quest_2.isActive == true && quest_2.isComplete == false)
                sfRenderWindow_drawSprite(main_window,Enemy.Sprite,NULL);
            
        }
        if(isIntersects_with_npc){
            if(quest_1.isComplete == false){
                sfRenderWindow_drawText(main_window, npc_replica1, NULL);
            }
            else if(quest_1.isComplete == true && quest_2.isComplete == false){
                sfRenderWindow_drawText(main_window, npc_replica2, NULL);
            } else if(quest_2.isComplete == true){
                sfRenderWindow_drawText(main_window, npc_replica3, NULL);
            }

            // _sleep(500);
            // quest_1.trigger = false;
        }
        if(isTabPressed){
            sfRenderWindow_drawSprite(main_window, qlist_spt, NULL);
            if(quest_1.isActive && quest_1.isComplete == false)
                sfRenderWindow_drawText(main_window, quest_1.text, NULL);
            if(quest_2.isActive && quest_2.isComplete == false)
                sfRenderWindow_drawText(main_window, quest_2.text, NULL);
        }
        sfRenderWindow_drawSprite(main_window,Character.Sprite,NULL);
        break;

    }
            
            sfRenderWindow_display(main_window);
        }
    
    return 0;
}
