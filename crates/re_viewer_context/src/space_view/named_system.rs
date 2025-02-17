use std::collections::{BTreeMap, BTreeSet};

use re_log_types::EntityPath;

re_string_interner::declare_new_type!(
    /// Unique name for a system within a given [`crate::SpaceViewClass`].
    ///
    /// Note that this is *not* unique across the entire application.
    #[derive(serde::Deserialize, serde::Serialize)]
    pub struct ViewSystemIdentifier;
);

impl Default for ViewSystemIdentifier {
    fn default() -> Self {
        "unknown".into()
    }
}

pub type PerSystemEntities = BTreeMap<ViewSystemIdentifier, BTreeSet<EntityPath>>;

/// Trait for naming/identifying [`crate::ViewPartSystem`]s & [`crate::ViewContextSystem`]s.
///
/// Required to be implemented for registration.
pub trait IdentifiedViewSystem {
    /// Unique name for a system within a given [`crate::SpaceViewClass`].
    ///
    /// Note that this is *not* unique across the entire application.
    fn identifier() -> ViewSystemIdentifier;
}
