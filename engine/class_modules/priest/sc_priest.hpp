// ==========================================================================
// Dedmonwakeen's Raid DPS/TPS Simulator.
// Send questions to natehieter@gmail.com
// ==========================================================================
//
// This file contains all definitions for priests. Implementations should
// be done on sc_priest.cpp if they are shared by more than one spec or
// in the respective spec file if they are limited to one spec only.

#pragma once
#include "simulationcraft.hpp"

#include "player/covenant.hpp"
#include "player/pet_spawner.hpp"
#include "sc_enums.hpp"

namespace priestspace
{
/* Forward declarations
 */
struct priest_t;

namespace actions
{
namespace spells
{
struct mind_sear_tick_t;
struct shadowy_apparition_spell_t;
struct angelic_feather_t;
struct divine_star_t;
struct apotheosis_t;
struct halo_t;
struct levitate_t;
struct smite_t;
struct summon_pet_t;
struct summon_shadowfiend_t;
struct summon_mindbender_t;
struct ascended_eruption_t;
struct psychic_link_t;
}  // namespace spells
namespace heals
{
struct power_word_shield_t;
struct insanity_drain_stacks_t;
}  // namespace heals
}  // namespace actions

namespace buffs
{
struct dispersion_t;
}

namespace pets
{
struct void_tendril_t;
}

/**
 * Priest target data
 * Contains target specific things
 */
struct priest_td_t final : public actor_target_data_t
{
public:
  struct dots_t
  {
    propagate_const<dot_t*> shadow_word_pain;
    propagate_const<dot_t*> vampiric_touch;
    propagate_const<dot_t*> devouring_plague;
    propagate_const<dot_t*> unholy_transfusion;
  } dots;

  struct buffs_t
  {
    propagate_const<buff_t*> schism;
    propagate_const<buff_t*> death_and_madness_debuff;
    propagate_const<buff_t*> surrender_to_madness_debuff;
  } buffs;

  priest_t& priest()
  {
    return *debug_cast<priest_t*>( source );
  }
  const priest_t& priest() const
  {
    return *debug_cast<priest_t*>( source );
  }

  priest_td_t( player_t* target, priest_t& p );
  void reset();
  void target_demise();
};

/**
 * Priest class definition
 * Derived from player_t. Contains everything that defines the priest class.
 */
struct priest_t final : public player_t
{
public:
  using base_t = player_t;

  // Buffs
  struct
  {
    // Talents
    propagate_const<buff_t*> twist_of_fate;

    // Shared
    propagate_const<buff_t*> power_infusion;

    // Discipline
    propagate_const<buff_t*> inner_focus;
    propagate_const<buff_t*> power_of_the_dark_side;
    propagate_const<buff_t*> sins_of_the_many;
    propagate_const<buff_t*> shadow_covenant;

    // Holy
    propagate_const<buff_t*> apotheosis;

    // Shadow
    propagate_const<buffs::dispersion_t*> dispersion;
    propagate_const<buff_t*> insanity_drain_stacks;
    propagate_const<buff_t*> shadowform;
    propagate_const<buff_t*> shadowform_state;  // Dummy buff to track whether player entered Shadowform initially
    propagate_const<buff_t*> shadowy_insight;
    propagate_const<buff_t*> surrender_to_madness;
    propagate_const<buff_t*> surrender_to_madness_death;
    propagate_const<buff_t*> vampiric_embrace;
    propagate_const<buff_t*> void_torrent;
    propagate_const<buff_t*> voidform;
    propagate_const<buff_t*> death_and_madness_buff;
    propagate_const<buff_t*> unfurling_darkness;
    propagate_const<buff_t*> unfurling_darkness_cd;  // Blizzard uses a buff to track the ICD
    propagate_const<buff_t*> ancient_madness;
    propagate_const<buff_t*> dark_thoughts;

    // Azerite Powers
    // Shadow
    propagate_const<buff_t*> chorus_of_insanity;
    propagate_const<buff_t*> harvested_thoughts;
    propagate_const<buff_t*> whispers_of_the_damned;

    // Runeforge Legendary
    propagate_const<buff_t*> the_penitent_one;

    // Conduits
    propagate_const<buff_t*> mind_devourer;
    propagate_const<buff_t*> blessing_of_plenty;  // Dummy buff to track CDR from Void Bolt

    // Covenants
    propagate_const<buff_t*> fae_blessings;
    propagate_const<buff_t*> boon_of_the_ascended;
  } buffs;

  // Talents
  struct
  {
    // Shared
    const spell_data_t* mindbender;
    const spell_data_t* twist_of_fate;
    const spell_data_t* angelic_feather;
    const spell_data_t* body_and_soul;  // NYI
    const spell_data_t* shining_force;
    const spell_data_t* psychic_voice;
    const spell_data_t* divine_star;
    const spell_data_t* halo;

    // Discipline
    // T15
    const spell_data_t* castigation;
    const spell_data_t* schism;
    // T25
    const spell_data_t* masochism;  // NYI
    // T30
    const spell_data_t* shield_discipline;  // NYI
    const spell_data_t* power_word_solace;
    // T35
    const spell_data_t* dominant_mind;  // NYI
    // T40
    const spell_data_t* sins_of_the_many;
    const spell_data_t* contrition;       // NYI
    const spell_data_t* shadow_covenant;  // NYI
    // T45
    const spell_data_t* purge_the_wicked;
    // T50
    const spell_data_t* lights_caress;     // NYI
    const spell_data_t* luminous_barrier;  // NYI
    const spell_data_t* evangelism;        // NYI

    // Holy
    // T15
    const spell_data_t* enlightenment;     // NYI
    const spell_data_t* trail_of_light;    // NYI
    const spell_data_t* enduring_renewal;  // NYI
    // T25
    const spell_data_t* angels_mercy;  // NYI
    // T30
    const spell_data_t* cosmic_ripple;   // NYI
    const spell_data_t* guardian_angel;  // NYI
    const spell_data_t* after_life;      // NYI
    // T35
    const spell_data_t* censure;  // NYI
    // T40
    const spell_data_t* surge_of_light;  // NYI
    const spell_data_t* binding_heal;    // NYI
    const spell_data_t* prayer_circle;   // NYI
    // T45
    const spell_data_t* benediction;  // NYI
    // T50
    const spell_data_t* light_of_the_naaru;  // NYI
    const spell_data_t* apotheosis;
    const spell_data_t* holy_word_salvation;  // NYI

    // Shadow
    // T15
    const spell_data_t* fortress_of_the_mind;
    const spell_data_t* death_and_madness;
    const spell_data_t* unfurling_darkness;
    // T25
    const spell_data_t* sanlayn;        // NYI
    const spell_data_t* intangibility;  // NYI
    // T30
    const spell_data_t* searing_nightmare;
    const spell_data_t* misery;
    // T35
    const spell_data_t* last_word;
    const spell_data_t* mind_bomb;
    const spell_data_t* psychic_horror;
    // T40
    const spell_data_t* auspicious_spirits;
    const spell_data_t* psychic_link;
    const spell_data_t* shadow_crash;
    // T45
    const spell_data_t* damnation;
    const spell_data_t* void_torrent;
    // T50
    const spell_data_t* legacy_of_the_void;
    const spell_data_t* ancient_madness;
    const spell_data_t* surrender_to_madness;
  } talents;

  // Specialization Spells
  struct
  {
    const spell_data_t* priest;  /// General priest data

    // Discipline
    const spell_data_t* discipline;  /// General discipline data
    const spell_data_t* discipline_priest;
    const spell_data_t* power_of_the_dark_side;  /// For buffing the damage of penance

    // Holy
    const spell_data_t* holy;  /// General holy data
    const spell_data_t* rapid_renewal;
    const spell_data_t* holy_words;
    const spell_data_t* holy_word_chastise;
    const spell_data_t* holy_word_serenity;
    const spell_data_t* holy_nova;
    const spell_data_t* holy_fire;
    const spell_data_t* apotheosis;
    const spell_data_t* serendipity;
    const spell_data_t* divine_providence;

    const spell_data_t* focused_will;
    const spell_data_t* holy_priest;

    // Shadow
    const spell_data_t* shadow;  /// General shadow data
    const spell_data_t* shadowy_apparitions;
    const spell_data_t* voidform;
    const spell_data_t* void_eruption;
    const spell_data_t* shadow_priest;
    const spell_data_t* dark_thoughts;

  } specs;

  // Mastery Spells
  struct
  {
    const spell_data_t* grace;
    const spell_data_t* echo_of_light;
    const spell_data_t* madness;
  } mastery_spells;

  // Cooldowns
  struct
  {
    // Shared

    // Shadow
    propagate_const<cooldown_t*> void_bolt;
    propagate_const<cooldown_t*> mind_blast;
    propagate_const<cooldown_t*> void_eruption;

    // Holy
    propagate_const<cooldown_t*> holy_word_serenity;
    propagate_const<cooldown_t*> holy_fire;
  } cooldowns;

  struct realppm_t
  {
    propagate_const<real_ppm_t*> eternal_call_to_the_void;
  } rppm;

  // Gains
  struct
  {
    propagate_const<gain_t*> mindbender;
    propagate_const<gain_t*> power_word_solace;
    propagate_const<gain_t*> insanity_auspicious_spirits;
    propagate_const<gain_t*> insanity_dispersion;
    propagate_const<gain_t*> insanity_drain;
    propagate_const<gain_t*> insanity_pet;
    propagate_const<gain_t*> insanity_surrender_to_madness;
    propagate_const<gain_t*> insanity_blessing;
    propagate_const<gain_t*> shadowy_insight;
    propagate_const<gain_t*> vampiric_touch_health;
    propagate_const<gain_t*> insanity_death_throes;
    propagate_const<gain_t*> power_of_the_dark_side;
    propagate_const<gain_t*> insanity_lucid_dreams;
    propagate_const<gain_t*> insanity_memory_of_lucid_dreams;
    propagate_const<gain_t*> shadow_word_death_self_damage;
    propagate_const<gain_t*> insanity_death_and_madness;
    propagate_const<gain_t*> insanity_mindgames;
    propagate_const<gain_t*> insanity_eternal_call_to_the_void;
    propagate_const<gain_t*> insanity_mind_sear;
  } gains;

  // Benefits
  struct
  {
  } benefits;

  // Procs
  struct
  {
    propagate_const<proc_t*> shadowy_insight;
    propagate_const<proc_t*> shadowy_insight_overflow;
    propagate_const<proc_t*> serendipity;
    propagate_const<proc_t*> serendipity_overflow;
    propagate_const<proc_t*> shadowy_apparition;
    propagate_const<proc_t*> shadowy_apparition_overflow;
    propagate_const<proc_t*> surge_of_light;
    propagate_const<proc_t*> surge_of_light_overflow;
    propagate_const<proc_t*> holy_fire_cd;
    propagate_const<proc_t*> power_of_the_dark_side;
    propagate_const<proc_t*> power_of_the_dark_side_overflow;
    propagate_const<proc_t*> shimmering_apparitions;
    propagate_const<proc_t*> dissonant_echoes;
    propagate_const<proc_t*> mind_devourer;
    propagate_const<proc_t*> blessing_of_plenty;
    propagate_const<proc_t*> void_tendril;
    propagate_const<proc_t*> dark_thoughts_flay;
    propagate_const<proc_t*> dark_thoughts_sear;
    propagate_const<proc_t*> dark_thoughts_missed;
  } procs;

  // Special
  struct
  {
    propagate_const<actions::spells::mind_sear_tick_t*> mind_sear_tick;
    propagate_const<actions::spells::shadowy_apparition_spell_t*> shadowy_apparitions;
    propagate_const<actions::spells::psychic_link_t*> psychic_link;
  } active_spells;

  // Items
  struct
  {
  } active_items;

  // Pets
  struct priest_pets_t
  {
    propagate_const<pet_t*> shadowfiend;
    propagate_const<pet_t*> mindbender;
    spawner::pet_spawner_t<pets::void_tendril_t, priest_t> void_tendril;

    priest_pets_t( priest_t& p );
  } pets;

  // Options
  struct
  {
    bool autoUnshift                              = true;  // Shift automatically out of stance/form
    bool priest_fixed_time                        = true;
    bool priest_ignore_healing                    = false;  // Remove Healing calculation codes
    int priest_set_voidform_duration              = 0;      // Voidform will always have this duration
    double priest_lucid_dreams_proc_chance_disc   = 0.08;
    double priest_lucid_dreams_proc_chance_holy   = 0.08;
    double priest_lucid_dreams_proc_chance_shadow = 0.15;

    // Add in easy options to change if you are in range or not
    bool priest_use_ascended_nova     = true;
    bool priest_use_ascended_eruption = true;

    // Add in options to override insanity gained
    // Mindgames gives 20 insanity from the healing and 20 from damage dealt
    /// For most content the healing part won't proc, only default damage dealt
    bool priest_mindgames_healing_insanity = false;
    bool priest_mindgames_damage_insanity  = true;

    // Fae Blessings CDR is not guarenteed to go on the Priest, reduce this to make things more accurate
    double priest_fae_blessings_cdr_chance = 1.00;
  } options;

  struct actions_t
  {
    actions::spells::ascended_eruption_t* ascended_eruption;
  } action;

  // Azerite
  struct azerite_t
  {
    // Holy
    azerite_power_t sacred_flame;
    // Disc
    azerite_power_t depth_of_the_shadows;
    // Shadow
    azerite_power_t chorus_of_insanity;
    azerite_power_t death_throes;
    azerite_power_t searing_dialogue;
    azerite_power_t spiteful_apparitions;
    azerite_power_t thought_harvester;
    azerite_power_t torment_of_torments;
    azerite_power_t whispers_of_the_damned;
  } azerite;

  struct
  {
    const spell_data_t* lucid_dreams;
    const spell_data_t* memory_of_lucid_dreams;
    azerite_essence_t vision_of_perfection;
    const spell_data_t* vision_of_perfection_r1;
    const spell_data_t* vision_of_perfection_r2;
  } azerite_essence;

  struct
  {
    // Generic Priest
    item_runeforge_t twins_of_the_sun_priestess;  // only used with Conduit to reduce CD of PI
    // Holy
    item_runeforge_t divine_image;          // NYI
    item_runeforge_t harmonious_apparatus;  // NYI
    // Disc
    item_runeforge_t kiss_of_death;
    item_runeforge_t the_penitent_one;  // Effect implemented, but not hooked up to PW:Radiance
    // Shadow
    item_runeforge_t painbreaker_psalm;
    item_runeforge_t shadowflame_prism;  // TODO: Add 20% damage modifier
    item_runeforge_t eternal_call_to_the_void;
    item_runeforge_t talbadars_stratagem;
  } legendary;

  struct
  {
    // Generic Priest
    conduit_data_t power_unto_others;
    // Holy
    conduit_data_t holy_oration;  // NYI
    // Discipline
    conduit_data_t swift_penitence;  // NYI
    // Shadow
    conduit_data_t dissonant_echoes;
    conduit_data_t mind_devourer;
    conduit_data_t rabid_shadows;
    conduit_data_t shimmering_apparitions;
    // Covenant
    conduit_data_t courageous_ascension;
    conduit_data_t festering_transfusion;
    conduit_data_t blessing_of_plenty;
    conduit_data_t shattered_perceptions;
  } conduits;

  struct
  {
    const spell_data_t* fae_blessings;
    const spell_data_t* unholy_nova;
    const spell_data_t* mindgames;
    const spell_data_t* boon_of_the_ascended;
  } covenant;

  struct insanity_end_event_t;

  priest_t( sim_t* sim, util::string_view name, race_e r );

  // player_t overrides
  void init_base_stats() override;
  void init_resources( bool force ) override;
  void init_spells() override;
  void create_buffs() override;
  void init_scaling() override;
  void init_background_actions() override;
  void reset() override;
  void create_options() override;
  std::string create_profile( save_e ) override;
  action_t* create_action( util::string_view name, const std::string& options ) override;
  pet_t* create_pet( util::string_view name, util::string_view type = "" ) override;
  void create_pets() override;
  void copy_from( player_t* source ) override;
  resource_e primary_resource() const override
  {
    return RESOURCE_MANA;
  }
  role_e primary_role() const override;
  stat_e convert_hybrid_stat( stat_e s ) const override;
  void assess_damage( school_e school, result_amount_type dtype, action_state_t* s ) override;
  double composite_melee_haste() const override;
  double composite_spell_haste() const override;
  double composite_spell_crit_chance() const override;
  double composite_player_pet_damage_multiplier( const action_state_t* ) const override;
  double composite_player_absorb_multiplier( const action_state_t* s ) const override;
  double composite_player_heal_multiplier( const action_state_t* s ) const override;
  double composite_player_target_multiplier( player_t* t, school_e school ) const override;
  double matching_gear_multiplier( attribute_e attr ) const override;
  void target_mitigation( school_e, result_amount_type, action_state_t* ) override;
  void init_action_list() override;
  void combat_begin() override;
  void init_rng() override;
  priest_td_t* get_target_data( player_t* target ) const override;
  std::unique_ptr<expr_t> create_expression( util::string_view name_str ) override;
  void arise() override;
  void vision_of_perfection_proc() override;
  void do_dynamic_regen() override;
  void apply_affecting_auras( action_t& ) override;

private:
  void create_cooldowns();
  void create_gains();
  void create_procs();
  void create_benefits();
  void create_apl_precombat();
  void create_apl_default();

  void create_buffs_shadow();
  void init_rng_shadow();
  void init_spells_shadow();
  void generate_apl_shadow();
  std::unique_ptr<expr_t> create_expression_shadow( util::string_view name_str );
  action_t* create_action_shadow( util::string_view name, util::string_view options_str );

  void create_buffs_discipline();
  void init_spells_discipline();
  void init_rng_discipline();

  void init_background_actions_shadow();
  void generate_apl_discipline_d();
  void generate_apl_discipline_h();
  std::unique_ptr<expr_t> create_expression_discipline( action_t* a, const util::string_view name_str );
  action_t* create_action_discipline( util::string_view name, util::string_view options_str );

  void create_buffs_holy();
  void init_spells_holy();
  void init_rng_holy();
  void generate_apl_holy_d();
  void generate_apl_holy_h();
  expr_t* create_expression_holy( action_t* a, util::string_view name_str );
  action_t* create_action_holy( util::string_view name, util::string_view options_str );

  target_specific_t<priest_td_t> _target_data;

public:
  void generate_insanity( double num_amount, gain_t* g, action_t* action );
  void lose_insanity( double amount, gain_t* g, action_t* action );
  void trigger_lucid_dreams( double cost );
  bool insanity_drain_frozen() const;
  void adjust_holy_word_serenity_cooldown();
  double tick_damage_over_time( timespan_t duration, const dot_t* dot ) const;
  void trigger_eternal_call_to_the_void( const dot_t* d );
  void trigger_shadowy_apparitions( action_state_t* );
  void trigger_psychic_link( action_state_t* );
  const priest_td_t* find_target_data( player_t* target ) const
  {
    return _target_data[ target ];
  }

  /**
   * Insanity tracking
   *
   * Handles the resource gaining from abilities, and insanity draining and manages an event that forcibly punts the
   * actor out of Voidform the exact moment insanity hitszero (millisecond resolution).
   */
  struct insanity_state_t final
  {
    event_t* end;             // End event for dropping out of voidform (insanity reaches 0)
    timespan_t last_drained;  // Timestamp when insanity was last drained
    priest_t& actor;

    const double base_drain_per_sec;
    const double stack_drain_multiplier;
    double base_drain_multiplier;

    insanity_state_t( priest_t& a );

    /// Deferred init for actor dependent stuff not ready in the ctor
    void init();

    /// Start the insanity drain tracking
    void set_last_drained();

    /// Start (or re-start) tracking of the insanity drain plus end event
    void begin_tracking();

    timespan_t time_to_end() const;

    void reset();

    /// Compute insanity drain per second with current state of the actor
    double insanity_drain_per_second() const;

    /// Gain some insanity
    void gain( double value, gain_t* gain_obj, action_t* source_action = nullptr );

    /// Lose some insanity
    void lose( double value, gain_t* gain_obj, action_t* source_action = nullptr );

    /**
     * Triggers the insanity drain, and is called in places that changes the insanity state of the actor in a relevant
     * way.
     * These are:
     * - Right before the actor decides to do something (scans APL for an ability to use)
     * - Right before insanity drain stack increases (every second)
     */
    void drain();

    /**
     * Predict (with current state) when insanity is going to be fully depleted, and adjust (or create) an event for it.
     * Called in conjunction with insanity_state_t::drain(), after the insanity drain occurs (and potentially after a
     * relevant state change such as insanity drain stack buff increase occurs). */
    void adjust_end_event();
  } insanity;

  std::string default_potion() const override;
  std::string default_flask() const override;
  std::string default_food() const override;
  std::string default_rune() const override;
};

namespace pets
{
/**
 * Pet base class
 *
 * Defines characteristics common to ALL priest pets.
 */
struct priest_pet_t : public pet_t
{
  priest_pet_t( sim_t* sim, priest_t& owner, util::string_view pet_name, pet_e pt, bool guardian = false )
    : pet_t( sim, &owner, pet_name, pt, guardian )
  {
  }

  void init_base_stats() override
  {
    pet_t::init_base_stats();

    base.position = POSITION_BACK;
    base.distance = 3;

    owner_coeff.ap_from_sp = 1.0;
    owner_coeff.sp_from_sp = 1.0;
  }

  void schedule_ready( timespan_t delta_time, bool waiting ) override
  {
    if ( main_hand_attack && !main_hand_attack->execute_event )
    {
      main_hand_attack->schedule_execute();
    }

    pet_t::schedule_ready( delta_time, waiting );
  }

  double composite_player_multiplier( school_e school ) const override
  {
    double m = pet_t::composite_player_multiplier( school );

    // Orc racial
    m *= 1.0 + o().racials.command->effectN( 1 ).percent();

    return m;
  }

  resource_e primary_resource() const override
  {
    return RESOURCE_ENERGY;
  }

  priest_t& o()
  {
    return static_cast<priest_t&>( *owner );
  }
  const priest_t& o() const
  {
    return static_cast<priest_t&>( *owner );
  }
};

struct priest_pet_melee_t : public melee_attack_t
{
  bool first_swing;

  priest_pet_melee_t( priest_pet_t& p, util::string_view name )
    : melee_attack_t( name, &p, spell_data_t::nil() ), first_swing( true )
  {
    school            = SCHOOL_SHADOW;
    weapon            = &( p.main_hand_weapon );
    weapon_multiplier = 1.0;
    base_execute_time = weapon->swing_time;
    may_crit          = true;
    background        = true;
    repeating         = true;
  }

  void reset() override
  {
    melee_attack_t::reset();
    first_swing = true;
  }

  timespan_t execute_time() const override
  {
    // First swing comes instantly after summoning the pet
    if ( first_swing )
      return timespan_t::zero();

    return melee_attack_t::execute_time();
  }

  void schedule_execute( action_state_t* state = nullptr ) override
  {
    melee_attack_t::schedule_execute( state );

    first_swing = false;
  }
};

struct priest_pet_spell_t : public spell_t
{
  priest_pet_spell_t( priest_pet_t& p, util::string_view n ) : spell_t( n, &p, p.find_pet_spell( n ) )
  {
    may_crit = true;
  }

  priest_pet_spell_t( util::string_view token, priest_pet_t* p, const spell_data_t* s = spell_data_t::nil() )
    : spell_t( token, p, s )
  {
    may_crit = true;
  }

  priest_pet_t& p()
  {
    return static_cast<priest_pet_t&>( *player );
  }
  const priest_pet_t& p() const
  {
    return static_cast<priest_pet_t&>( *player );
  }
};

namespace fiend
{
/**
 * Abstract base class for Shadowfiend and Mindbender
 */
struct base_fiend_pet_t : public priest_pet_t
{
  struct gains_t
  {
    propagate_const<gain_t*> fiend;
  } gains;

  double direct_power_mod;

  base_fiend_pet_t( sim_t* sim, priest_t& owner, pet_e pt, util::string_view name )
    : priest_pet_t( sim, owner, name, pt ), gains(), direct_power_mod( 0.0 )
  {
    main_hand_weapon.type       = WEAPON_BEAST;
    main_hand_weapon.swing_time = timespan_t::from_seconds( 1.5 );

    owner_coeff.health = 0.3;
  }

  virtual double mana_return_percent() const = 0;
  virtual double insanity_gain() const       = 0;

  void init_action_list() override;

  void init_gains() override
  {
    priest_pet_t::init_gains();

    if ( o().specialization() == PRIEST_SHADOW )
    {
      gains.fiend = o().gains.insanity_pet;
    }
    else
    {
      switch ( pet_type )
      {
        case PET_MINDBENDER:
        {
          gains.fiend = o().gains.mindbender;
        }
        break;
        default:
          gains.fiend = get_gain( "basefiend" );
          break;
      }
    }
  }

  void init_resources( bool force ) override
  {
    priest_pet_t::init_resources( force );

    resources.initial[ RESOURCE_MANA ] = owner->resources.max[ RESOURCE_MANA ];
    resources.current = resources.max = resources.initial;
  }

  double composite_player_multiplier( school_e school ) const override;
  double composite_melee_haste() const override;

  action_t* create_action( util::string_view name, const std::string& options_str ) override;
};

struct shadowfiend_pet_t final : public base_fiend_pet_t
{
  shadowfiend_pet_t( sim_t* sim, priest_t& owner, util::string_view name = "shadowfiend" )
    : base_fiend_pet_t( sim, owner, PET_SHADOWFIEND, name )
  {
    direct_power_mod = 0.6;  // According to Sephuz 2018-02-07 -- N1gh7h4wk hardcoded

    main_hand_weapon.min_dmg = owner.dbc->spell_scaling( owner.type, owner.level() ) * 2;
    main_hand_weapon.max_dmg = owner.dbc->spell_scaling( owner.type, owner.level() ) * 2;

    main_hand_weapon.damage = ( main_hand_weapon.min_dmg + main_hand_weapon.max_dmg ) / 2;
  }

  double mana_return_percent() const override
  {
    return 0.0;
  }
  double insanity_gain() const override
  {
    return o().find_spell( 262485 )->effectN( 1 ).resource( RESOURCE_INSANITY );
  }
};

struct mindbender_pet_t final : public base_fiend_pet_t
{
  const spell_data_t* mindbender_spell;

  mindbender_pet_t( sim_t* sim, priest_t& owner, util::string_view name = "mindbender" )
    : base_fiend_pet_t( sim, owner, PET_MINDBENDER, name ), mindbender_spell( owner.find_spell( 123051 ) )
  {
    direct_power_mod = 0.65;  // According to Sephuz 2018-02-07 -- N1gh7h4wk hardcoded

    main_hand_weapon.min_dmg = owner.dbc->spell_scaling( owner.type, owner.level() ) * 2;
    main_hand_weapon.max_dmg = owner.dbc->spell_scaling( owner.type, owner.level() ) * 2;
    main_hand_weapon.damage  = ( main_hand_weapon.min_dmg + main_hand_weapon.max_dmg ) / 2;
  }

  double mana_return_percent() const override
  {
    double m = mindbender_spell->effectN( 1 ).percent();
    return m / 100;
  }
  double insanity_gain() const override
  {
    return o().find_spell( 200010 )->effectN( 1 ).resource( RESOURCE_INSANITY );
  }
};

namespace actions
{
struct shadowcrawl_t final : public priest_pet_spell_t
{
  shadowcrawl_t( base_fiend_pet_t& p ) : priest_pet_spell_t( p, "Shadowcrawl" )
  {
    may_miss = false;
    harmful  = false;
  }

  base_fiend_pet_t& p()
  {
    return static_cast<base_fiend_pet_t&>( *player );
  }
  const base_fiend_pet_t& p() const
  {
    return static_cast<base_fiend_pet_t&>( *player );
  }
};

struct fiend_melee_t : public priest_pet_melee_t
{
  fiend_melee_t( base_fiend_pet_t& p ) : priest_pet_melee_t( p, "melee" )
  {
    weapon                  = &( p.main_hand_weapon );
    weapon_multiplier       = 0.0;
    base_dd_min             = weapon->min_dmg;
    base_dd_max             = weapon->max_dmg;
    attack_power_mod.direct = p.direct_power_mod;
  }

  base_fiend_pet_t& p()
  {
    return static_cast<base_fiend_pet_t&>( *player );
  }
  const base_fiend_pet_t& p() const
  {
    return static_cast<base_fiend_pet_t&>( *player );
  }

  timespan_t execute_time() const override
  {
    if ( base_execute_time == timespan_t::zero() )
      return timespan_t::zero();

    if ( !harmful && !player->in_combat )
      return timespan_t::zero();

    return base_execute_time * player->cache.spell_speed();
  }

  void impact( action_state_t* s ) override
  {
    priest_pet_melee_t::impact( s );

    if ( result_is_hit( s->result ) )
    {
      if ( p().o().specialization() == PRIEST_SHADOW )
      {
        double amount = p().insanity_gain();
        if ( p().o().buffs.surrender_to_madness->up() )
        {
          p().o().resource_gain(
              RESOURCE_INSANITY,
              ( amount * ( 1.0 + p().o().talents.surrender_to_madness->effectN( 2 ).percent() ) ) - amount,
              p().o().gains.insanity_surrender_to_madness );
        }
        p().o().insanity.gain( amount, p().gains.fiend, nullptr );
      }
      else
      {
        double mana_reg_pct = p().mana_return_percent();
        if ( mana_reg_pct > 0.0 )
        {
          p().o().resource_gain( RESOURCE_MANA, p().o().resources.max[ RESOURCE_MANA ] * p().mana_return_percent(),
                                 p().gains.fiend );
        }
      }
    }
  }
};
}  // namespace actions
}  // namespace fiend

struct void_tendril_t final : public priest_pet_t
{
  void_tendril_t( priest_t* owner ) : priest_pet_t( owner->sim, *owner, "void_tendril", PET_VOID_TENDRIL, true )
  {
  }

  void init_action_list() override
  {
    priest_pet_t::init_action_list();

    action_priority_list_t* def = get_action_priority_list( "default" );
    def->add_action( "mind_flay" );
  }

  action_t* create_action( util::string_view name, const std::string& options_str ) override;
};

}  // namespace pets

namespace actions
{
/**
 * Priest action base class
 *
 * This is a template for common code between priest_spell_t, priest_heal_t and priest_absorb_t.
 * The template is instantiated with either spell_t, heal_t or absorb_t as the 'Base' class.
 * Make sure you keep the inheritance hierarchy and use base_t in the derived class, don't skip it and call
 * spell_t/heal_t or absorb_t directly.
 */
template <typename Base>
struct priest_action_t : public Base
{
  struct
  {
    bool voidform_da;
    bool voidform_ta;
    bool shadowform_da;
    bool shadowform_ta;
    bool twist_of_fate_da;
    bool twist_of_fate_ta;
    bool mastery_madness_da;
    bool mastery_madness_ta;
    bool shadow_covenant_da;
    bool shadow_covenant_ta;
  } affected_by;

  double vf_da_multiplier;
  double vf_ta_multiplier;

public:
  priest_action_t( util::string_view name, priest_t& p, const spell_data_t* s = spell_data_t::nil() )
    : ab( name, &p, s ), affected_by(), vf_da_multiplier( 1 ), vf_ta_multiplier( 1 )
  {
    init_affected_by();
    ab::may_crit          = true;
    ab::tick_may_crit     = true;
    ab::weapon_multiplier = 0.0;

    if ( p.talents.sins_of_the_many->ok() )
    {
      ab::base_dd_multiplier *= 1.0 + p.talents.sins_of_the_many->effectN( 1 ).percent();
      ab::base_td_multiplier *= 1.0 + p.talents.sins_of_the_many->effectN( 1 ).percent();
    }

    if ( affected_by.voidform_da )
    {
      vf_da_multiplier = 1 + priest().buffs.voidform->data().effectN( 1 ).percent() +
                         priest().talents.legacy_of_the_void->effectN( 4 ).percent();
    }
    if ( affected_by.voidform_ta )
    {
      vf_ta_multiplier = 1 + priest().buffs.voidform->data().effectN( 2 ).percent() +
                         priest().talents.legacy_of_the_void->effectN( 4 ).percent();
    }
  }

  /**
   * Initialize all affected_by members and print out debug info
   */
  void init_affected_by()
  {
    struct affect_init_t
    {
      const spelleffect_data_t& effect;
      bool& affects;
    } affects[] = {{priest().buffs.voidform->data().effectN( 1 ), affected_by.voidform_da},
                   {priest().buffs.voidform->data().effectN( 2 ), affected_by.voidform_ta},
                   {priest().buffs.shadowform->data().effectN( 1 ), affected_by.shadowform_da},
                   {priest().buffs.shadowform->data().effectN( 4 ), affected_by.shadowform_ta},
                   {priest().buffs.twist_of_fate->data().effectN( 1 ), affected_by.twist_of_fate_da},
                   {priest().buffs.twist_of_fate->data().effectN( 2 ), affected_by.twist_of_fate_ta},
                   {priest().mastery_spells.madness->effectN( 1 ), affected_by.mastery_madness_da},
                   {priest().mastery_spells.madness->effectN( 2 ), affected_by.mastery_madness_ta},
                   {priest().buffs.shadow_covenant->data().effectN( 2 ), affected_by.shadow_covenant_da},
                   {priest().buffs.shadow_covenant->data().effectN( 3 ), affected_by.shadow_covenant_ta}};

    for ( const auto& a : affects )
    {
      a.affects = base_t::data().affected_by( a.effect );
      if ( a.affects && ab::sim->debug )
      {
        ab::sim->print_debug( "{} {} ({}) affected by {} (idx={}).", *ab::player, *this, ab::data().id(),
                              a.effect.spell()->name_cstr(), a.effect.spell_effect_num() + 1 );
      }
    }
  }

  priest_td_t& get_td( player_t* t )
  {
    return *( priest().get_target_data( t ) );
  }

  const priest_td_t* find_td( player_t* t ) const
  {
    return priest().find_target_data( t );
  }

  bool trigger_shadowy_insight()
  {
    int stack = priest().buffs.shadowy_insight->check();
    if ( priest().buffs.shadowy_insight->trigger() )
    {
      priest().cooldowns.mind_blast->reset( true );

      if ( priest().buffs.shadowy_insight->check() == stack )
      {
        priest().procs.shadowy_insight_overflow->occur();
      }
      else
      {
        priest().procs.shadowy_insight->occur();
      }
      return true;
    }
    return false;
  };

  void trigger_power_of_the_dark_side()
  {
    int stack = priest().buffs.power_of_the_dark_side->check();
    if ( priest().buffs.power_of_the_dark_side->trigger() )
    {
      if ( priest().buffs.power_of_the_dark_side->check() == stack )
      {
        priest().procs.power_of_the_dark_side_overflow->occur();
      }
      else
      {
        priest().procs.power_of_the_dark_side->occur();
      }
    }
  }

  double cost() const override
  {
    double c = ab::cost();

    return c;
  }

  double action_da_multiplier() const override
  {
    double m = ab::action_da_multiplier();

    if ( affected_by.mastery_madness_da )
    {
      m *= 1.0 + priest().cache.mastery_value();
    }
    if ( affected_by.voidform_da && priest().buffs.voidform->check() )
    {
      m *= vf_da_multiplier;
    }
    if ( affected_by.shadowform_da && priest().buffs.shadowform->check() )
    {
      m *= 1.0 + priest().buffs.shadowform->data().effectN( 1 ).percent();
    }
    if ( affected_by.twist_of_fate_da && priest().buffs.twist_of_fate->check() )
    {
      m *= 1.0 + priest().buffs.twist_of_fate->data().effectN( 1 ).percent();
    }
    if ( affected_by.shadow_covenant_da && priest().buffs.shadow_covenant->check() )
    {
      m *= 1 + priest().buffs.shadow_covenant->data().effectN( 2 ).percent();
    }
    return m;
  }

  double action_ta_multiplier() const override
  {
    double m = ab::action_ta_multiplier();

    if ( affected_by.mastery_madness_ta )
    {
      m *= 1.0 + priest().cache.mastery_value();
    }
    if ( affected_by.voidform_ta && priest().buffs.voidform->check() )
    {
      m *= vf_ta_multiplier;
    }
    if ( affected_by.shadowform_ta && priest().buffs.shadowform->check() )
    {
      m *= 1.0 + priest().buffs.shadowform->data().effectN( 4 ).percent();
    }
    if ( affected_by.twist_of_fate_ta && priest().buffs.twist_of_fate->check() )
    {
      m *= 1.0 + priest().buffs.twist_of_fate->data().effectN( 2 ).percent();
    }
    if ( affected_by.shadow_covenant_ta && priest().buffs.shadow_covenant->check() )
    {
      m *= 1 + priest().buffs.shadow_covenant->data().effectN( 3 ).percent();
    }
    return m;
  }

  void gain_energize_resource( resource_e resource_type, double amount, gain_t* gain ) override
  {
    if ( resource_type == RESOURCE_INSANITY )
    {
      priest().generate_insanity( amount, gain, this );
    }
    else
    {
      ab::gain_energize_resource( resource_type, amount, gain );
    }
  }

protected:
  priest_t& priest()
  {
    return *debug_cast<priest_t*>( ab::player );
  }
  const priest_t& priest() const
  {
    return *debug_cast<priest_t*>( ab::player );
  }

  /// typedef for priest_action_t<action_base_t>
  using base_t = priest_action_t;

private:
  /// typedef for the templated action type, eg. spell_t, attack_t, heal_t
  using ab = Base;
};

struct priest_absorb_t : public priest_action_t<absorb_t>
{
public:
  priest_absorb_t( util::string_view name, priest_t& player, const spell_data_t* s = spell_data_t::nil() )
    : base_t( name, player, s )
  {
    may_crit      = true;
    tick_may_crit = false;
    may_miss      = false;
  }
};

struct priest_heal_t : public priest_action_t<heal_t>
{
  priest_heal_t( util::string_view name, priest_t& player, const spell_data_t* s = spell_data_t::nil() )
    : base_t( name, player, s )
  {
  }

  void execute() override
  {
    base_t::execute();

    may_crit = true;
  }

  void impact( action_state_t* s ) override
  {
    double save_health_percentage = s->target->health_percentage();

    base_t::impact( s );

    if ( s->result_amount > 0 )
    {
      if ( priest().specialization() != PRIEST_SHADOW && priest().talents.twist_of_fate->ok() &&
           ( save_health_percentage < priest().talents.twist_of_fate->effectN( 1 ).base_value() ) )
      {
        priest().buffs.twist_of_fate->trigger();
      }
    }
  }
};

struct priest_spell_t : public priest_action_t<spell_t>
{
  priest_spell_t( util::string_view name, priest_t& player, const spell_data_t* s = spell_data_t::nil() )
    : base_t( name, player, s )
  {
    weapon_multiplier = 0.0;
  }

  bool usable_moving() const override
  {
    if ( priest().buffs.surrender_to_madness->check() )
    {
      return true;
    }

    return base_t::usable_moving();
  }

  bool ready() override
  {
    if ( priest().specialization() == PRIEST_SHADOW && priest().talents.surrender_to_madness->ok() )
    {
      if ( priest().buffs.surrender_to_madness_death->check() )
      {
        return false;
      }
    }

    return action_t::ready();
  }

  void consume_resource() override
  {
    auto resource = current_resource();

    base_t::consume_resource();

    if ( resource == RESOURCE_INSANITY )
    {
      priest().insanity.adjust_end_event();
    }

    if ( priest().specialization() != PRIEST_SHADOW )
      priest().trigger_lucid_dreams( last_resource_cost );
  }

  void impact( action_state_t* s ) override
  {
    double save_health_percentage = s->target->health_percentage();

    base_t::impact( s );

    if ( result_is_hit( s->result ) )
    {
      if ( priest().specialization() == PRIEST_SHADOW && priest().talents.twist_of_fate->ok() &&
           ( save_health_percentage < priest().talents.twist_of_fate->effectN( 1 ).base_value() ) )
      {
        priest().buffs.twist_of_fate->trigger();
      }
    }
  }

  double get_death_throes_bonus() const
  {
    if ( priest().azerite.death_throes.enabled() )
    {
      auto value = priest().azerite.death_throes.value( 1 );
      if ( priest().specs.discipline_priest->ok() )
      {
        value *= ( 100.0 + priest().specs.discipline_priest->effectN( 8 ).base_value() ) / 100.0;
      }
      return value;
    }

    return 0.0;
  }

  void assess_damage( result_amount_type type, action_state_t* s ) override
  {
    base_t::assess_damage( type, s );

    if ( aoe == 0 && result_is_hit( s->result ) && priest().buffs.vampiric_embrace->up() )
      trigger_vampiric_embrace( s );
  }

  /* Based on previous implementation ( pets don't count but get full heal )
   * and https://www.wowhead.com/spell=15286#comments:id=1796701
   * Last checked 2013-05-25
   */
  void trigger_vampiric_embrace( action_state_t* s )
  {
    double amount = s->result_amount;
    amount *= priest().buffs.vampiric_embrace->data().effectN( 1 ).percent();  // FIXME additive or multiplicate?

    for ( player_t* ally : sim->player_no_pet_list )
    {
      if ( ally->current.sleeping )
      {
        continue;
      }
      ally->resource_gain( RESOURCE_HEALTH, amount, ally->gains.vampiric_embrace );

      for ( pet_t* pet : ally->pet_list )
      {
        pet->resource_gain( RESOURCE_HEALTH, amount, pet->gains.vampiric_embrace );
      }
    }
  }
};

}  // namespace actions

namespace buffs
{
/**
 * This is a template for common code between priest buffs.
 * The template is instantiated with any type of buff ( buff_t, debuff_t,
 * absorb_buff_t, etc. ) as the 'Base' class.
 * Make sure you keep the inheritance hierarchy and use base_t in the derived
 * class,
 * don't skip it and call buff_t/absorb_buff_t/etc. directly.
 */
template <typename Base = buff_t>
struct priest_buff_t : public Base
{
public:
  using base_t = priest_buff_t;  // typedef for priest_buff_t<buff_base_t>

  priest_buff_t( priest_td_t& td, util::string_view name, const spell_data_t* s = spell_data_t::nil(),
                 const item_t* item = nullptr )
    : Base( td, name, s, item )
  {
  }

  priest_buff_t( priest_t& p, util::string_view name, const spell_data_t* s = spell_data_t::nil(),
                 const item_t* item = nullptr )
    : Base( &p, name, s, item )
  {
  }

protected:
  priest_t& priest()
  {
    return *debug_cast<priest_t*>( Base::source );
  }
  const priest_t& priest() const
  {
    return *debug_cast<priest_t*>( Base::source );
  }
};

struct dispersion_t final : public priest_buff_t<buff_t>
{
  bool no_insanty_drain;

  dispersion_t( priest_t& p );
};

}  // namespace buffs

namespace items
{
void init();
}  // namespace items

/**
 * Report Extension Class
 * Here you can define class specific report extensions/overrides
 */
struct priest_report_t final : public player_report_extension_t
{
public:
  priest_report_t( priest_t& player ) : p( player )
  {
  }

  void html_customsection( report::sc_html_stream& /* os*/ ) override
  {
    (void)p;
    /*// Custom Class Section
    os << "\t\t\t\t<div class=\"player-section custom_section\">\n"
    << "\t\t\t\t\t<h3 class=\"toggle open\">Custom Section</h3>\n"
    << "\t\t\t\t\t<div class=\"toggle-content\">\n";

    os << p.name();

    os << "\t\t\t\t\t\t</div>\n" << "\t\t\t\t\t</div>\n";*/
  }

private:
  priest_t& p;
};

struct priest_module_t final : public module_t
{
  priest_module_t() : module_t( PRIEST )
  {
  }

  player_t* create_player( sim_t* sim, util::string_view name, race_e r = RACE_NONE ) const override
  {
    auto p              = new priest_t( sim, name, r );
    p->report_extension = std::unique_ptr<player_report_extension_t>( new priest_report_t( *p ) );
    return p;
  }
  bool valid() const override
  {
    return true;
  }
  void init( player_t* p ) const override
  {
    p->buffs.guardian_spirit = make_buff( p, "guardian_spirit",
                                          p->find_spell( 47788 ) );  // Let the ability handle the CD
    p->buffs.pain_supression = make_buff( p, "pain_supression",
                                          p->find_spell( 33206 ) );  // Let the ability handle the CD
  }
  void static_init() const override
  {
    items::init();
  }
  void register_hotfixes() const override
  {
  }
  void combat_begin( sim_t* ) const override
  {
  }
  void combat_end( sim_t* ) const override
  {
  }
};

/**
 * Adjust maximum charges for a cooldown
 * Takes the cooldown and new maximum charge count
 * Function depends on the internal working of cooldown_t::reset
 */
static void adjust_max_charges( cooldown_t* cooldown, int new_max_charges )
{
  assert( new_max_charges > 0 && "Cooldown charges must be greater than 0" );
  assert( cooldown && "Cooldown must not be null" );

  int charges_max = cooldown->charges;

  // Charges are not being changed, just end.
  if ( charges_max == new_max_charges )
    return;

  /**
   * If the cooldown ongoing we can assume that the action isn't a nullptr as otherwise the action would not be ongoing.
   * If it has no action we cannot call cooldown->start which means we cannot set fractional charges.
   * However, a cooldown is not ongoing at maximum charges. if we have maximum charges then the number of charges will
   * only ever change equal to the change in maximum charges. This means we'll never need to use cooldown->start to
   * handle the case where cooldown is not ongoing and cooldown->reset is satisfactory.
   */
  if ( !cooldown->ongoing() )
  {
    // Change charges to new max
    cooldown->charges = new_max_charges;
    // Call reset, which will set current charges to new max and make relevant event calls
    cooldown->reset( false, -1 );
  }
  else
  {
    action_t* cooldown_action = cooldown->action;
    double charges_fractional = cooldown->charges_fractional();

    if ( new_max_charges < charges_max )
    {
      /**
       * If our new max charges is less than current max charges, we have lost maximum charges.
       * If we have lost maximum charges, we'll also lose current charges for charges lost but we'll keep current
       * cooldown progress.
       **/
      int charges_lost   = charges_max - new_max_charges;
      charges_fractional = charges_fractional >= charges_lost ? charges_fractional - charges_lost
                                                              : charges_fractional - floor( charges_fractional );
    }
    else
    {
      /**
       * Otherwise, we have gained maximum charges.
       * Gaining maximum charges will give us those charges.
       **/
      int charges_gained = new_max_charges - charges_max;
      charges_fractional += charges_gained;
    }

    // Set new maximum charges then reset to stop all events.
    cooldown->charges = new_max_charges;
    cooldown->reset( false, -1 );

    /**
     * This loop is used to remove all of the charges and start the cooldown recovery event properly.
     * It does it by repetetively calling cooldown->start which will remove a current charge and restart the event
     * timers.
     */
    for ( int i = 0; i < cooldown->charges; i++ )
      cooldown->start( cooldown_action );

    /**
     * Use adjust to go from 0 charges and 0 cooldown progress to the previously calculated charges we should have after
     * changing max charges by making the cooldown advance in time by the multiple of the cooldown.
     */
    cooldown->adjust( -charges_fractional * cooldown_t::cooldown_duration( cooldown ) );
  }
}

}  // namespace priestspace
