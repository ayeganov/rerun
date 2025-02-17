// DO NOT EDIT! This file was auto-generated by crates/re_types_builder/src/codegen/cpp/mod.rs
// Based on "crates/re_types/definitions/rerun/archetypes/bar_chart.fbs".

#pragma once

#include "../collection.hpp"
#include "../compiler_utils.hpp"
#include "../components/color.hpp"
#include "../components/tensor_data.hpp"
#include "../data_cell.hpp"
#include "../indicator_component.hpp"
#include "../result.hpp"

#include <cstdint>
#include <optional>
#include <utility>
#include <vector>

namespace rerun::archetypes {
    /// **Archetype**: A bar chart.
    ///
    /// The x values will be the indices of the array, and the bar heights will be the provided values.
    ///
    /// ## Example
    ///
    /// ### Simple bar chart
    /// ![image](https://static.rerun.io/barchart_simple/cf6014b18265edfcaa562c06526c0716b296b193/full.png)
    ///
    /// ```cpp
    /// #include <rerun.hpp>
    ///
    /// int main() {
    ///     const auto rec = rerun::RecordingStream("rerun_example_bar_chart");
    ///     rec.spawn().exit_on_failure();
    ///
    ///     rec.log("bar_chart", rerun::BarChart::i64({8, 4, 0, 9, 1, 4, 1, 6, 9, 0}));
    /// }
    /// ```
    struct BarChart {
        /// The values. Should always be a rank-1 tensor.
        rerun::components::TensorData values;

        /// The color of the bar chart
        std::optional<rerun::components::Color> color;

      public:
        static constexpr const char IndicatorComponentName[] = "rerun.components.BarChartIndicator";

        /// Indicator component, used to identify the archetype when converting to a list of components.
        using IndicatorComponent = components::IndicatorComponent<IndicatorComponentName>;

      public:
        // Extensions to generated type defined in 'bar_chart_ext.cpp'

        BarChart(rerun::datatypes::TensorBuffer buffer) {
            auto num_elems = buffer.num_elems();
            this->values = rerun::components::TensorData({num_elems}, std::move(buffer));
        }

        // --------------------------------------------------------------------
        // Implicit constructors:

        /// Construct a `BarChart` from a `Collection<uint8_t>`.
        BarChart(Collection<uint8_t> u8)
            : BarChart(rerun::datatypes::TensorBuffer::u8(std::move(u8))) {}

        /// Construct a `BarChart` from a `Collection<uint16_t>`.
        BarChart(Collection<uint16_t> u16)
            : BarChart(rerun::datatypes::TensorBuffer::u16(std::move(u16))) {}

        /// Construct a `BarChart` from a `Collection<uint32_t>`.
        BarChart(Collection<uint32_t> u32)
            : BarChart(rerun::datatypes::TensorBuffer::u32(std::move(u32))) {}

        /// Construct a `BarChart` from a `Collection<uint64_t>`.
        BarChart(Collection<uint64_t> u64)
            : BarChart(rerun::datatypes::TensorBuffer::u64(std::move(u64))) {}

        /// Construct a `BarChart` from a `Collection<int8_t>`.
        BarChart(Collection<int8_t> i8)
            : BarChart(rerun::datatypes::TensorBuffer::i8(std::move(i8))) {}

        /// Construct a `BarChart` from a `Collection<int16_t>`.
        BarChart(Collection<int16_t> i16)
            : BarChart(rerun::datatypes::TensorBuffer::i16(std::move(i16))) {}

        /// Construct a `BarChart` from a `Collection<int32_t>`.
        BarChart(Collection<int32_t> i32)
            : BarChart(rerun::datatypes::TensorBuffer::i32(std::move(i32))) {}

        /// Construct a `BarChart` from a `Collection<int64_t>`.
        BarChart(Collection<int64_t> i64)
            : BarChart(rerun::datatypes::TensorBuffer::i64(std::move(i64))) {}

        /// Construct aBarChart` from a `Collection<half>`.
        BarChart(Collection<rerun::half> f16)
            : BarChart(rerun::datatypes::TensorBuffer::f16(std::move(f16))) {}

        /// Construct a `BarChart` from a `Collection<float>`.
        BarChart(Collection<float> f32)
            : BarChart(rerun::datatypes::TensorBuffer::f32(std::move(f32))) {}

        /// Construct a `BarChart` from a `Collection<double>`.
        BarChart(Collection<double> f64)
            : BarChart(rerun::datatypes::TensorBuffer::f64(std::move(f64))) {}

        // --------------------------------------------------------------------
        // Explicit static constructors:

        /// Construct a `BarChart` from a `Collection<uint8_t>`.
        static BarChart u8(Collection<uint8_t> u8) {
            return BarChart(std::move(u8));
        }

        /// Construct a `BarChart` from a `Collection<uint16_t>`.
        static BarChart u16(Collection<uint16_t> u16) {
            return BarChart(std::move(u16));
        }

        /// Construct a `BarChart` from a `Collection<uint32_t>`.
        static BarChart u32(Collection<uint32_t> u32) {
            return BarChart(std::move(u32));
        }

        /// Construct a `BarChart` from a `Collection<uint64_t>`.
        static BarChart u64(Collection<uint64_t> u64) {
            return BarChart(std::move(u64));
        }

        /// Construct a `BarChart` from a `Collection<int8_t>`.
        static BarChart i8(Collection<int8_t> i8) {
            return BarChart(std::move(i8));
        }

        /// Construct a `BarChart` from a `Collection<int16_t>`.
        static BarChart i16(Collection<int16_t> i16) {
            return BarChart(std::move(i16));
        }

        /// Construct a `BarChart` from a `Collection<int32_t>`.
        static BarChart i32(Collection<int32_t> i32) {
            return BarChart(std::move(i32));
        }

        /// Construct a `BarChart` from a `Collection<int64_t>`.
        static BarChart i64(Collection<int64_t> i64) {
            return BarChart(std::move(i64));
        }

        /// Construct a `BarChart` from a  `Collection<half>`.
        static BarChart f16(Collection<rerun::half> f16) {
            return BarChart(std::move(f16));
        }

        /// Construct a `BarChart` from a `Collection<float>`.
        static BarChart f32(Collection<float> f32) {
            return BarChart(std::move(f32));
        }

        /// Construct a `BarChart` from a `Collection<double>`.
        static BarChart f64(Collection<double> f64) {
            return BarChart(std::move(f64));
        }

      public:
        BarChart() = default;
        BarChart(BarChart&& other) = default;

        explicit BarChart(rerun::components::TensorData _values) : values(std::move(_values)) {}

        /// The color of the bar chart
        BarChart with_color(rerun::components::Color _color) && {
            color = std::move(_color);
            // See: https://github.com/rerun-io/rerun/issues/4027
            RR_WITH_MAYBE_UNINITIALIZED_DISABLED(return std::move(*this);)
        }

        /// Returns the number of primary instances of this archetype.
        size_t num_instances() const {
            return 1;
        }
    };

} // namespace rerun::archetypes

namespace rerun {
    /// \private
    template <typename T>
    struct AsComponents;

    /// \private
    template <>
    struct AsComponents<archetypes::BarChart> {
        /// Serialize all set component batches.
        static Result<std::vector<DataCell>> serialize(const archetypes::BarChart& archetype);
    };
} // namespace rerun
