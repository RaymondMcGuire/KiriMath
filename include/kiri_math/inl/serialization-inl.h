

#ifndef _KIRI_MATH_DETAIL_SERIALIZATION_INL_H_
#define _KIRI_MATH_DETAIL_SERIALIZATION_INL_H_

#include <kiri_math/serialization.h>

#include <cstring>
#include <vector>

namespace kiri_math
{

    template <typename T>
    void serialize(const ConstArrayAccessor1<T> &array,
                   std::vector<uint8_t> *buffer)
    {
        size_t size = sizeof(T) * array.size();
        serialize(reinterpret_cast<const uint8_t *>(array.data()), size, buffer);
    }

    template <typename T>
    void deserialize(const std::vector<uint8_t> &buffer, Array1<T> *array)
    {
        std::vector<uint8_t> data;
        deserialize(buffer, &data);
        array->resize(data.size() / sizeof(T));
        memcpy(reinterpret_cast<uint8_t *>(array->data()), data.data(), data.size());
    }

} // namespace kiri_math

#endif // _KIRI_MATH_DETAIL_SERIALIZATION_INL_H_
