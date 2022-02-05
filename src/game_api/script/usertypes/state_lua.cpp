#include "state_lua.hpp"

#include "game_manager.hpp"
#include "level_api.hpp"
#include "online.hpp"
#include "rpc.hpp"
#include "state.hpp"

#include <sol/sol.hpp>

namespace NState
{
void register_usertypes(sol::state& lua)
{
    lua.new_usertype<ArenaConfigArenas>(
        "ArenaConfigArenas",
        "dwelling_1",
        &ArenaConfigArenas::dwelling_1,
        "dwelling_2",
        &ArenaConfigArenas::dwelling_2,
        "dwelling_3",
        &ArenaConfigArenas::dwelling_3,
        "dwelling_4",
        &ArenaConfigArenas::dwelling_4,
        "dwelling_5",
        &ArenaConfigArenas::dwelling_5,
        "jungle_1",
        &ArenaConfigArenas::jungle_1,
        "jungle_2",
        &ArenaConfigArenas::jungle_2,
        "jungle_3",
        &ArenaConfigArenas::jungle_3,
        "jungle_4",
        &ArenaConfigArenas::jungle_4,
        "jungle_5",
        &ArenaConfigArenas::jungle_5,
        "volcana_1",
        &ArenaConfigArenas::volcana_1,
        "volcana_2",
        &ArenaConfigArenas::volcana_2,
        "volcana_3",
        &ArenaConfigArenas::volcana_3,
        "volcana_4",
        &ArenaConfigArenas::volcana_4,
        "volcana_5",
        &ArenaConfigArenas::volcana_5,
        "tidepool_1",
        &ArenaConfigArenas::tidepool_1,
        "tidepool_2",
        &ArenaConfigArenas::tidepool_2,
        "tidepool_3",
        &ArenaConfigArenas::tidepool_3,
        "tidepool_4",
        &ArenaConfigArenas::tidepool_4,
        "tidepool_5",
        &ArenaConfigArenas::tidepool_5,
        "temple_1",
        &ArenaConfigArenas::temple_1,
        "temple_2",
        &ArenaConfigArenas::temple_2,
        "temple_3",
        &ArenaConfigArenas::temple_3,
        "temple_4",
        &ArenaConfigArenas::temple_4,
        "temple_5",
        &ArenaConfigArenas::temple_5,
        "icecaves_1",
        &ArenaConfigArenas::icecaves_1,
        "icecaves_2",
        &ArenaConfigArenas::icecaves_2,
        "icecaves_3",
        &ArenaConfigArenas::icecaves_3,
        "icecaves_4",
        &ArenaConfigArenas::icecaves_4,
        "icecaves_5",
        &ArenaConfigArenas::icecaves_5,
        "neobabylon_1",
        &ArenaConfigArenas::neobabylon_1,
        "neobabylon_2",
        &ArenaConfigArenas::neobabylon_2,
        "neobabylon_3",
        &ArenaConfigArenas::neobabylon_3,
        "neobabylon_4",
        &ArenaConfigArenas::neobabylon_4,
        "neobabylon_5",
        &ArenaConfigArenas::neobabylon_5,
        "sunkencity_1",
        &ArenaConfigArenas::sunkencity_1,
        "sunkencity_2",
        &ArenaConfigArenas::sunkencity_2,
        "sunkencity_3",
        &ArenaConfigArenas::sunkencity_3,
        "sunkencity_4",
        &ArenaConfigArenas::sunkencity_4,
        "sunkencity_5",
        &ArenaConfigArenas::sunkencity_5);

    lua.new_usertype<ArenaConfigItems>(
        "ArenaConfigItems",
        "rock",
        &ArenaConfigItems::rock,
        "pot",
        &ArenaConfigItems::pot,
        "bombbag",
        &ArenaConfigItems::bombbag,
        "bombbox",
        &ArenaConfigItems::bombbox,
        "ropepile",
        &ArenaConfigItems::ropepile,
        "pickup_12bag",
        &ArenaConfigItems::pickup_12bag,
        "pickup_24bag",
        &ArenaConfigItems::pickup_24bag,
        "cooked_turkey",
        &ArenaConfigItems::cooked_turkey,
        "royal_jelly",
        &ArenaConfigItems::royal_jelly,
        "torch",
        &ArenaConfigItems::torch,
        "boomerang",
        &ArenaConfigItems::boomerang,
        "machete",
        &ArenaConfigItems::machete,
        "mattock",
        &ArenaConfigItems::mattock,
        "crossbow",
        &ArenaConfigItems::crossbow,
        "webgun",
        &ArenaConfigItems::webgun,
        "freezeray",
        &ArenaConfigItems::freezeray,
        "shotgun",
        &ArenaConfigItems::shotgun,
        "camera",
        &ArenaConfigItems::camera,
        "plasma_cannon",
        &ArenaConfigItems::plasma_cannon,
        "wooden_shield",
        &ArenaConfigItems::wooden_shield,
        "metal_shield",
        &ArenaConfigItems::metal_shield,
        "teleporter",
        &ArenaConfigItems::teleporter,
        "mine",
        &ArenaConfigItems::mine,
        "snaptrap",
        &ArenaConfigItems::snaptrap,
        "paste",
        &ArenaConfigItems::paste,
        "climbing_gloves",
        &ArenaConfigItems::climbing_gloves,
        "pitchers_mitt",
        &ArenaConfigItems::pitchers_mitt,
        "spike_shoes",
        &ArenaConfigItems::spike_shoes,
        "spring_shoes",
        &ArenaConfigItems::spring_shoes,
        "parachute",
        &ArenaConfigItems::parachute,
        "cape",
        &ArenaConfigItems::cape,
        "vlads_cape",
        &ArenaConfigItems::vlads_cape,
        "jetpack",
        &ArenaConfigItems::jetpack,
        "hoverpack",
        &ArenaConfigItems::hoverpack,
        "telepack",
        &ArenaConfigItems::telepack,
        "powerpack",
        &ArenaConfigItems::powerpack,
        "excalibur",
        &ArenaConfigItems::excalibur,
        "scepter",
        &ArenaConfigItems::scepter,
        "kapala",
        &ArenaConfigItems::kapala,
        "true_crown",
        &ArenaConfigItems::true_crown);

    lua.new_usertype<ArenaConfigEquippedItems>(
        "ArenaConfigEquippedItems",
        "paste",
        &ArenaConfigEquippedItems::paste,
        "climbing_gloves",
        &ArenaConfigEquippedItems::climbing_gloves,
        "pitchers_mitt",
        &ArenaConfigEquippedItems::pitchers_mitt,
        "spike_shoes",
        &ArenaConfigEquippedItems::spike_shoes,
        "spring_shoes",
        &ArenaConfigEquippedItems::spring_shoes,
        "parachute",
        &ArenaConfigEquippedItems::parachute,
        "kapala",
        &ArenaConfigEquippedItems::kapala,
        "scepter",
        &ArenaConfigEquippedItems::scepter);

    lua.new_usertype<ArenaState>(
        "ArenaState",
        "current_arena",
        &ArenaState::current_arena,
        "player_teams",
        &ArenaState::player_teams,
        "format",
        &ArenaState::format,
        "ruleset",
        &ArenaState::ruleset,
        "player_lives",
        &ArenaState::player_lives,
        "player_totalwins",
        &ArenaState::player_totalwins,
        "player_won",
        &ArenaState::player_won,
        "timer",
        &ArenaState::timer,
        "timer_ending",
        &ArenaState::timer_ending,
        "wins",
        &ArenaState::wins,
        "lives",
        &ArenaState::lives,
        "player_idolheld_countdown",
        &ArenaState::player_idolheld_countdown,
        "health",
        &ArenaState::health,
        "bombs",
        &ArenaState::bombs,
        "ropes",
        &ArenaState::ropes,
        "stun_time",
        &ArenaState::stun_time,
        "mount",
        &ArenaState::mount,
        "arena_select",
        &ArenaState::arena_select,
        "arenas",
        &ArenaState::arenas,
        "dark_level_chance",
        &ArenaState::dark_level_chance,
        "crate_frequency",
        &ArenaState::crate_frequency,
        "items_enabled",
        &ArenaState::items_enabled,
        "items_in_crate",
        &ArenaState::items_in_crate,
        "held_item",
        &ArenaState::held_item,
        "equipped_backitem",
        &ArenaState::equipped_backitem,
        "equipped_items",
        &ArenaState::equipped_items,
        "whip_damage",
        &ArenaState::whip_damage,
        "final_ghost",
        &ArenaState::final_ghost,
        "breath_cooldown",
        &ArenaState::breath_cooldown,
        "punish_ball",
        &ArenaState::punish_ball);

    lua.new_usertype<SelectPlayerSlot>(
        "SelectPlayerSlot",
        "activated",
        &SelectPlayerSlot::activated,
        "character",
        &SelectPlayerSlot::character,
        "texture",
        &SelectPlayerSlot::texture_id);
    lua.new_usertype<Items>(
        "Items",
        "player_count",
        &Items::player_count,
        "saved_pets_count",
        &Items::saved_pets_count,
        "saved_pets",
        &Items::saved_pets,
        "is_pet_cursed",
        &Items::is_pet_cursed,
        "is_pet_poisoned",
        &Items::is_pet_poisoned,

        // had to be done this way as autodoc doesn't like sol::property stuff
        /*"player_inventory",
        &Items::player_inventories,*/
        /*"player_select",
        &Items::player_select_slots,*/
        //); stop autodoc here

        "player_select",
        sol::property([](Items& s)
                      { return std::ref(s.player_select_slots); }),
        "player_inventory",
        sol::property([](Items& s)
                      { return std::ref(s.player_inventories); }));

    auto state_usertype = lua.new_usertype<StateMemory>(
        "StateMemory",
        "screen_last",
        &StateMemory::screen_last,
        "screen",
        &StateMemory::screen,
        "screen_next",
        &StateMemory::screen_next,
        "ingame",
        &StateMemory::ingame,
        "playing",
        &StateMemory::playing,
        "pause",
        &StateMemory::pause,
        "width",
        &StateMemory::w,
        "height",
        &StateMemory::h,
        "kali_favor",
        &StateMemory::kali_favor,
        "kali_status",
        &StateMemory::kali_status,
        "kali_altars_destroyed",
        &StateMemory::kali_altars_destroyed,
        "kali_gifts",
        &StateMemory::kali_gifts,
        "seed",
        &StateMemory::seed,
        "time_total",
        &StateMemory::time_total,
        "world",
        &StateMemory::world,
        "world_next",
        &StateMemory::world_next,
        "world_start",
        &StateMemory::world_start,
        "level",
        &StateMemory::level,
        "level_next",
        &StateMemory::level_next,
        "level_start",
        &StateMemory::level_start,
        "theme",
        &StateMemory::theme,
        "theme_next",
        &StateMemory::theme_next,
        "theme_start",
        &StateMemory::theme_start,
        "force_current_theme",
        &StateMemory::force_current_theme,
        "shoppie_aggro",
        &StateMemory::shoppie_aggro,
        "shoppie_aggro_next",
        &StateMemory::shoppie_aggro_levels,
        "merchant_aggro",
        &StateMemory::merchant_aggro,
        "kills_npc",
        &StateMemory::kills_npc,
        "level_count",
        &StateMemory::level_count,
        "damage_taken",
        &StateMemory::damage_taken,
        "journal_flags",
        &StateMemory::journal_flags,
        "time_last_level",
        &StateMemory::time_last_level,
        "time_level",
        &StateMemory::time_level,
        "level_flags",
        &StateMemory::level_flags,
        "loading",
        &StateMemory::loading,
        "quest_flags",
        &StateMemory::quest_flags,
        "presence_flags",
        &StateMemory::presence_flags,
        "fadevalue",
        &StateMemory::fadevalue,
        "fadeout",
        &StateMemory::fadeout,
        "fadein",
        &StateMemory::fadein,
        "loading_black_screen_timer",
        &StateMemory::loading_black_screen_timer,
        "saved_dogs",
        &StateMemory::saved_dogs,
        "saved_cats",
        &StateMemory::saved_cats,
        "saved_hamsters",
        &StateMemory::saved_hamsters,
        "win_state",
        &StateMemory::win_state,
        "illumination",
        &StateMemory::illumination,
        "money_last_levels",
        &StateMemory::money_last_levels,
        "money_shop_total",
        &StateMemory::money_shop_total,
        "player_inputs",
        sol::readonly(&StateMemory::player_inputs),
        "quests",
        &StateMemory::quests,
        "camera",
        &StateMemory::camera,
        "special_visibility_flags",
        &StateMemory::special_visibility_flags,
        "cause_of_death",
        &StateMemory::cause_of_death,
        "cause_of_death_entity_type",
        &StateMemory::cause_of_death_entity_type,
        "toast_timer",
        &StateMemory::toast_timer,
        "speechbubble_timer",
        &StateMemory::speechbubble_timer,
        "speechbubble_owner",
        &StateMemory::speechbubble_owner,
        "level_gen",
        &StateMemory::level_gen,
        "correct_ushabti",
        &StateMemory::correct_ushabti,
        "items",
        &StateMemory::items,
        "camera_layer",
        &StateMemory::camera_layer,
        "screen_team_select",
        &StateMemory::screen_team_select,
        "screen_character_select",
        &StateMemory::screen_character_select,
        "screen_transition",
        &StateMemory::screen_transition,
        "screen_death",
        &StateMemory::screen_death,
        "screen_win",
        &StateMemory::screen_win,
        "screen_credits",
        &StateMemory::screen_credits,
        "screen_scores",
        &StateMemory::screen_scores,
        "screen_constellation",
        &StateMemory::screen_constellation,
        "screen_recap",
        &StateMemory::screen_recap,
        "screen_arena_stages_select",
        &StateMemory::screen_arena_stages_select1,
        "screen_arena_intro",
        &StateMemory::screen_arena_intro,
        "screen_arena_level",
        &StateMemory::screen_arena_level,
        "screen_arena_score",
        &StateMemory::screen_arena_score,
        "screen_arena_menu",
        &StateMemory::screen_arena_menu,
        "screen_arena_items",
        &StateMemory::screen_arena_items,
        "get_correct_ushabti",
        &StateMemory::get_correct_ushabti,
        "set_correct_ushabti",
        &StateMemory::set_correct_ushabti,
        "arena",
        &StateMemory::arena,
        /* state got so big that adding stuff here will couse `compiler out of heap space`
        * to solve this, we add stuff in this comment for the autodoc, and then for real below to the `state_usertype`

        "speedrun_character",
        &StateMemory::speedrun_character,
        "speedrun_activation_trigger",
        &StateMemory::speedrun_activation_trigger,
        "end_spaceship_character",
        &StateMemory::end_spaceship_character,
        "world2_coffin_spawned",
        &StateMemory::world2_coffin_spawned,
        "world4_coffin_spawned",
        &StateMemory::world4_coffin_spawned,
        "world6_coffin_spawned",
        &StateMemory::world6_coffin_spawned,
        "first_damage_cause",
        &StateMemory::first_damage_cause,
        "first_damage_world",
        &StateMemory::first_damage_world,
        "first_damage_level",
        &StateMemory::first_damage_level,
        "time_speedrun",
        &StateMemory::time_speedrun,
        "coffin_contents",
        &StateMemory::coffin_contents,
        "screen_change_counter",
        &StateMemory::screen_change_counter,
        "time_startup",
        &StateMemory::time_startup,
        */
        "logic",
        &StateMemory::logic); // had to have something at the at for the "comma" before the big comment block

    state_usertype["speedrun_character"] = &StateMemory::speedrun_character;
    state_usertype["speedrun_activation_trigger"] = &StateMemory::speedrun_activation_trigger;
    state_usertype["end_spaceship_character"] = &StateMemory::end_spaceship_character;
    state_usertype["world2_coffin_spawned"] = &StateMemory::world2_coffin_spawned;
    state_usertype["world4_coffin_spawned"] = &StateMemory::world4_coffin_spawned;
    state_usertype["world6_coffin_spawned"] = &StateMemory::world6_coffin_spawned;
    state_usertype["first_damage_cause"] = &StateMemory::first_damage_cause;
    state_usertype["first_damage_world"] = &StateMemory::first_damage_world;
    state_usertype["first_damage_level"] = &StateMemory::first_damage_level;
    state_usertype["time_speedrun"] = &StateMemory::time_speedrun;
    state_usertype["coffin_contents"] = &StateMemory::coffin_contents;
    state_usertype["screen_change_counter"] = &StateMemory::screen_change_counter;
    state_usertype["time_startup"] = &StateMemory::time_startup;

    lua.new_usertype<GameManager>(
        "GameManager",
        "game_props",
        &GameManager::game_props,
        "screen_logo",
        &GameManager::screen_logo,
        "screen_intro",
        &GameManager::screen_intro,
        "screen_prologue",
        &GameManager::screen_prologue,
        "screen_title",
        &GameManager::screen_title,
        "screen_menu",
        &GameManager::screen_menu,
        "screen_options",
        &GameManager::screen_options,
        "screen_player_profile",
        &GameManager::screen_player_profile,
        "screen_leaderboards",
        &GameManager::screen_leaderboards,
        "screen_seed_input",
        &GameManager::screen_seed_input,
        "screen_camp",
        &GameManager::screen_camp,
        "screen_level",
        &GameManager::screen_level,
        "screen_online_loading",
        &GameManager::screen_online_loading,
        "screen_online_lobby",
        &GameManager::screen_online_lobby,
        "pause_ui",
        &GameManager::pause_ui,
        "journal_ui",
        &GameManager::journal_ui,
        "save_related",
        &GameManager::save_related);
    lua.new_usertype<SaveRelated>(
        "SaveRelated",
        "journal_popup_ui",
        &SaveRelated::journal_popup_ui);
    lua.new_usertype<JournalPopupUI>(
        "JournalPopupUI",
        "wiggling_page_icon",
        &JournalPopupUI::wiggling_page_icon,
        "black_background",
        &JournalPopupUI::black_background,
        "button_icon",
        &JournalPopupUI::button_icon,
        "wiggling_page_angle",
        &JournalPopupUI::wiggling_page_angle,
        "chapter_to_show",
        &JournalPopupUI::chapter_to_show,
        "entry_to_show",
        &JournalPopupUI::entry_to_show,
        "timer",
        &JournalPopupUI::timer,
        "slide_position",
        &JournalPopupUI::slide_position);
    lua.new_usertype<GameProps>(
        "GameProps",
        "buttons",
        &GameProps::buttons,
        "game_has_focus",
        &GameProps::game_has_focus);
    lua.new_usertype<LightParams>(
        "LightParams",
        "red",
        &LightParams::red,
        "green",
        &LightParams::green,
        "blue",
        &LightParams::blue,
        "size",
        &LightParams::size);
    lua.new_usertype<Illumination>(
        "Illumination",
        "lights",
        &Illumination::lights,
        "light1",
        &Illumination::light1,
        "light2",
        &Illumination::light2,
        "light3",
        &Illumination::light3,
        "light4",
        &Illumination::light4,
        "brightness",
        &Illumination::brightness,
        "brightness_multiplier",
        &Illumination::brightness_multiplier,
        "light_pos_x",
        &Illumination::light_pos_x,
        "light_pos_y",
        &Illumination::light_pos_y,
        "offset_x",
        &Illumination::offset_x,
        "offset_y",
        &Illumination::offset_y,
        "distortion",
        &Illumination::distortion,
        "entity_uid",
        &Illumination::entity_uid,
        "flags",
        &Illumination::flags,
        "type_flags",
        &Illumination::type_flags,
        "enabled",
        &Illumination::enabled,
        "layer",
        &Illumination::layer);

    auto create_illumination = sol::overload(
        static_cast<Illumination* (*)(Color color, float size, float x, float y)>(::create_illumination),
        static_cast<Illumination* (*)(Color color, float size, uint32_t uid)>(::create_illumination));
    /// Creates a new Illumination. Don't forget to continuously call `refresh_illumination`, otherwise your light emitter fades out! Check out the illumination.lua script for an example
    lua["create_illumination"] = create_illumination;
    /// Refreshes an Illumination, keeps it from fading out
    lua["refresh_illumination"] = refresh_illumination;

    lua.new_usertype<Camera>(
        "Camera",
        "bounds_left",
        &Camera::bounds_left,
        "bounds_right",
        &Camera::bounds_right,
        "bounds_bottom",
        &Camera::bounds_bottom,
        "bounds_top",
        &Camera::bounds_top,
        "adjusted_focus_x",
        &Camera::adjusted_focus_x,
        "adjusted_focus_y",
        &Camera::adjusted_focus_y,
        "focus_offset_x",
        &Camera::focus_offset_x,
        "focus_offset_y",
        &Camera::focus_offset_y,
        "focus_x",
        &Camera::focus_x,
        "focus_y",
        &Camera::focus_y,
        "vertical_pan",
        &Camera::vertical_pan,
        "shake_countdown_start",
        &Camera::shake_countdown_start,
        "shake_countdown",
        &Camera::shake_countdown,
        "shake_amplitude",
        &Camera::shake_amplitude,
        "shake_multiplier_x",
        &Camera::shake_multiplier_x,
        "shake_multiplier_y",
        &Camera::shake_multiplier_y,
        "uniform_shake",
        &Camera::uniform_shake,
        "focused_entity_uid",
        &Camera::focused_entity_uid,
        "inertia",
        &Camera::inertia);
    lua.new_usertype<Online>(
        "Online",
        "online_players",
        &Online::online_players,
        "local_player",
        &Online::local_player,
        "lobby",
        &Online::lobby);
    lua.new_usertype<OnlinePlayer>(
        "OnlinePlayer",
        "ready_state",
        sol::readonly(&OnlinePlayer::ready_state),
        "character",
        &OnlinePlayer::character,
        "player_name",
        sol::readonly(&OnlinePlayer::player_name));
    lua.new_usertype<OnlineLobby>(
        "OnlineLobby",
        "code",
        &OnlineLobby::code,
        "get_code",
        &OnlineLobby::get_code);
    lua.new_usertype<LogicList>(
        "LogicList",
        "olmec_cutscene",
        &LogicList::olmec_cutscene,
        "tiamat_cutscene",
        &LogicList::tiamat_cutscene,
        "diceshop",
        &LogicList::diceshop);
    lua.new_usertype<Logic>(
        "Logic");
    lua.new_usertype<LogicOlmecCutscene>(
        "LogicOlmecCutscene",
        "olmec",
        &LogicOlmecCutscene::olmec,
        "player",
        &LogicOlmecCutscene::player,
        "cinematic_anchor",
        &LogicOlmecCutscene::cinematic_anchor,
        "timer",
        &LogicOlmecCutscene::timer,
        sol::base_classes,
        sol::bases<Logic>());
    lua.new_usertype<LogicTiamatCutscene>(
        "LogicTiamatCutscene",
        "tiamat",
        &LogicTiamatCutscene::tiamat,
        "player",
        &LogicTiamatCutscene::player,
        "cinematic_anchor",
        &LogicTiamatCutscene::cinematic_anchor,
        "timer",
        &LogicTiamatCutscene::timer,
        sol::base_classes,
        sol::bases<Logic>());
    lua.new_usertype<LogicDiceShop>(
        "LogicDiceShop",
        "bet_machine",
        &LogicDiceShop::bet_machine,
        "die1",
        &LogicDiceShop::die1,
        "die2",
        &LogicDiceShop::die2,
        "die_1_value",
        &LogicDiceShop::die_1_value,
        "die_2_value",
        &LogicDiceShop::die_2_value,
        "prize_dispenser",
        &LogicDiceShop::prize_dispenser,
        "prize",
        &LogicDiceShop::prize,
        "forcefield",
        &LogicDiceShop::forcefield,
        "bet_active",
        &LogicDiceShop::bet_active,
        "forcefield_deactivated",
        &LogicDiceShop::forcefield_deactivated,
        "boss_angry",
        &LogicDiceShop::boss_angry,
        "result_announcement_timer",
        &LogicDiceShop::result_announcement_timer,
        "won_prizes_count",
        &LogicDiceShop::won_prizes_count,
        "balance",
        &LogicDiceShop::balance,
        sol::base_classes,
        sol::bases<Logic>());

    lua.create_named_table("CAUSE_OF_DEATH", "DEATH", 0, "ENTITY", 1, "LONG_FALL", 2, "STILL_FALLING", 3, "MISSED", 4, "POISONED", 5);

    lua["toast_visible"] = []() -> bool
    {
        return State::get().ptr()->toast != 0;
    };

    lua["speechbubble_visible"] = []() -> bool
    {
        return State::get().ptr()->speechbubble != 0;
    };

    lua["cancel_toast"] = []()
    {
        State::get().ptr()->toast_timer = 1000;
    };

    lua["cancel_speechbubble"] = []()
    {
        State::get().ptr()->speechbubble_timer = 1000;
    };
}
}; // namespace NState
