#[derive(Clone, Copy, Debug)]
pub struct Icon {
    /// Human readable unique id
    pub id: &'static str,

    pub png_bytes: &'static [u8],
}

impl Icon {
    pub const fn new(id: &'static str, png_bytes: &'static [u8]) -> Self {
        Self { id, png_bytes }
    }
}

pub const RIGHT_PANEL_TOGGLE: Icon = Icon::new(
    "right_panel_toggle",
    include_bytes!("../data/icons/right_panel_toggle.png"),
);
pub const BOTTOM_PANEL_TOGGLE: Icon = Icon::new(
    "bottom_panel_toggle",
    include_bytes!("../data/icons/bottom_panel_toggle.png"),
);
pub const LEFT_PANEL_TOGGLE: Icon = Icon::new(
    "left_panel_toggle",
    include_bytes!("../data/icons/left_panel_toggle.png"),
);

pub const MINIMIZE: Icon = Icon::new("minimize", include_bytes!("../data/icons/minimize.png"));
pub const MAXIMIZE: Icon = Icon::new("maximize", include_bytes!("../data/icons/maximize.png"));
