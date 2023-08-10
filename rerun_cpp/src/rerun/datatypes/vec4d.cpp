// NOTE: This file was autogenerated by re_types_builder; DO NOT EDIT.
// Based on "crates/re_types/definitions/rerun/datatypes/vec4d.fbs"

#include "vec4d.hpp"

#include <arrow/api.h>

namespace rerun {
    namespace datatypes {
        const std::shared_ptr<arrow::DataType> &Vec4D::to_arrow_datatype() {
            static const auto datatype =
                arrow::fixed_size_list(arrow::field("item", arrow::float32(), false), 4);
            return datatype;
        }

        arrow::Result<std::shared_ptr<arrow::FixedSizeListBuilder>> Vec4D::new_arrow_array_builder(
            arrow::MemoryPool *memory_pool
        ) {
            if (!memory_pool) {
                return arrow::Status::Invalid("Memory pool is null.");
            }

            return arrow::Result(std::make_shared<arrow::FixedSizeListBuilder>(
                memory_pool,
                std::make_shared<arrow::FloatBuilder>(memory_pool),
                4
            ));
        }

        arrow::Status Vec4D::fill_arrow_array_builder(
            arrow::FixedSizeListBuilder *builder, const Vec4D *elements, size_t num_elements
        ) {
            if (!builder) {
                return arrow::Status::Invalid("Passed array builder is null.");
            }
            if (!elements) {
                return arrow::Status::Invalid("Cannot serialize null pointer to arrow array.");
            }

            auto value_builder = static_cast<arrow::FloatBuilder *>(builder->value_builder());

            ARROW_RETURN_NOT_OK(builder->AppendValues(num_elements));
            static_assert(sizeof(elements[0].xyzw) == sizeof(elements[0]));
            ARROW_RETURN_NOT_OK(
                value_builder->AppendValues(elements[0].xyzw, num_elements * 4, nullptr)
            );

            return arrow::Status::OK();
        }
    } // namespace datatypes
} // namespace rerun
