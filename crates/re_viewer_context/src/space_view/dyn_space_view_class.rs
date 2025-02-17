use re_data_store::{EntityProperties, EntityPropertyMap};
use re_log_types::EntityPath;
use re_types::ComponentName;

use crate::{
    AutoSpawnHeuristic, PerSystemEntities, SpaceViewClassRegistryError, SpaceViewId,
    SpaceViewSystemRegistry, SystemExecutionOutput, ViewQuery, ViewerContext,
};

re_string_interner::declare_new_type!(
    /// The unique name of a space view type.
    #[derive(serde::Deserialize, serde::Serialize)]
    pub struct SpaceViewClassIdentifier;
);

impl SpaceViewClassIdentifier {
    pub fn invalid() -> Self {
        Self::from("invalid")
    }
}

#[derive(Clone, Copy, Debug, Default, PartialEq, PartialOrd, Ord, Eq)]
pub enum SpaceViewClassLayoutPriority {
    /// This space view can share space with others
    ///
    /// Used for boring things like text and plots.
    Low,

    #[default]
    Medium,

    /// Give this space view lots of space.
    /// Used for spatial views (2D/3D).
    High,
}

/// Defines a class of space view without any concrete types making it suitable for storage and interfacing.
///
/// Implemented by [`crate::SpaceViewClass`].
///
/// Each Space View in the viewer's viewport has a single class assigned immutable at its creation time.
/// The class defines all aspects of its behavior.
/// It determines which entities are queried, how they are rendered, and how the user can interact with them.
pub trait DynSpaceViewClass: Send + Sync {
    /// Name of this space view class.
    ///
    /// Used for identification. Must be unique within a viewer session.
    fn identifier(&self) -> SpaceViewClassIdentifier;

    /// User-facing name of this space view class.
    ///
    /// Used for UI display.
    fn display_name(&self) -> &'static str;

    /// Icon used to identify this space view class.
    fn icon(&self) -> &'static re_ui::Icon;

    /// Help text describing how to interact with this space view in the ui.
    fn help_text(&self, re_ui: &re_ui::ReUi) -> egui::WidgetText;

    /// Called once upon registration of the class
    ///
    /// This can be used to register all built-in [`crate::ViewContextSystem`] and [`crate::ViewPartSystem`].
    fn on_register(
        &self,
        system_registry: &mut SpaceViewSystemRegistry,
    ) -> Result<(), SpaceViewClassRegistryError>;

    /// Called once for every new space view instance of this class.
    ///
    /// The state is *not* persisted across viewer sessions, only shared frame-to-frame.
    fn new_state(&self) -> Box<dyn SpaceViewState>;

    /// Optional archetype of the Space View's blueprint properties.
    ///
    /// Blueprint components that only apply to the space view itself, not to the entities it displays.
    fn blueprint_archetype(&self) -> Option<Vec<ComponentName>>;

    /// Preferred aspect ratio for the ui tiles of this space view.
    fn preferred_tile_aspect_ratio(&self, state: &dyn SpaceViewState) -> Option<f32>;

    /// Controls how likely this space view will get a large tile in the ui.
    fn layout_priority(&self) -> SpaceViewClassLayoutPriority;

    /// Heuristic used to determine which space view is the best fit for a set of paths.
    ///
    /// For each path in `ent_paths`, at least one of the registered [`crate::ViewPartSystem`] for this class
    /// returned true when calling [`crate::ViewPartSystem::heuristic_filter`].
    fn auto_spawn_heuristic(
        &self,
        _ctx: &ViewerContext<'_>,
        space_origin: &EntityPath,
        ent_paths: &PerSystemEntities,
    ) -> AutoSpawnHeuristic;

    /// Executed for all active space views on frame start (before any ui is drawn),
    /// can be use for heuristic & state updates before populating the scene.
    ///
    /// Is only allowed to access archetypes defined by [`Self::blueprint_archetype`]
    /// Passed entity properties are individual properties without propagated values.
    fn on_frame_start(
        &self,
        ctx: &ViewerContext<'_>,
        state: &mut dyn SpaceViewState,
        ent_paths: &PerSystemEntities,
        entity_properties: &mut EntityPropertyMap,
    );

    /// Ui shown when the user selects a space view of this class.
    ///
    /// TODO(andreas): Should this be instead implemented via a registered `data_ui` of all blueprint relevant types?
    fn selection_ui(
        &self,
        ctx: &ViewerContext<'_>,
        ui: &mut egui::Ui,
        state: &mut dyn SpaceViewState,
        space_origin: &EntityPath,
        space_view_id: SpaceViewId,
        root_entity_properties: &mut EntityProperties,
    );

    /// Draws the ui for this space view type and handles ui events.
    ///
    /// The state passed in was previously created by [`Self::new_state`] and is kept frame-to-frame.
    fn ui(
        &self,
        ctx: &ViewerContext<'_>,
        ui: &mut egui::Ui,
        state: &mut dyn SpaceViewState,
        root_entity_properties: &EntityProperties,
        query: &ViewQuery<'_>,
        system_output: SystemExecutionOutput,
    );
}

/// Unserialized frame to frame state of a space view.
///
/// For any state that should be persisted, use the Blueprint!
/// This state is used for transient state, such as animation or uncommitted ui state like dragging a camera.
/// (on mouse release, the camera would be committed to the blueprint).
pub trait SpaceViewState: std::any::Any {
    /// Converts itself to a reference of [`std::any::Any`], which enables downcasting to concrete types.
    fn as_any(&self) -> &dyn std::any::Any;

    /// Converts itself to a reference of [`std::any::Any`], which enables downcasting to concrete types.
    fn as_any_mut(&mut self) -> &mut dyn std::any::Any;
}

/// Implementation of an empty space view state.
impl SpaceViewState for () {
    fn as_any(&self) -> &dyn std::any::Any {
        self
    }

    fn as_any_mut(&mut self) -> &mut dyn std::any::Any {
        self
    }
}
