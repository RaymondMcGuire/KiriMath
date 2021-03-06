#ifdef _MSC_VER
#pragma warning(disable : 4244)
#endif

#include <kiri_math/pch.h>

#include <generated/flat_data_generated.h>

#include <kiri_math/serialization.h>

#include <vector>

namespace kiri_math
{

    void serialize(const Serializable *serializable, std::vector<uint8_t> *buffer)
    {
        serializable->serialize(buffer);
    }

    void serialize(const uint8_t *data, size_t size, std::vector<uint8_t> *buffer)
    {
        flatbuffers::FlatBufferBuilder builder(1024);

        auto fbsData = fbs::CreateFlatData(
            builder, builder.CreateVector(data, size));

        builder.Finish(fbsData);

        uint8_t *buf = builder.GetBufferPointer();
        size_t sz = builder.GetSize();

        buffer->resize(sz);
        memcpy(buffer->data(), buf, sz);
    }

    void deserialize(
        const std::vector<uint8_t> &buffer,
        Serializable *serializable)
    {
        serializable->deserialize(buffer);
    }

    void deserialize(
        const std::vector<uint8_t> &buffer, std::vector<uint8_t> *data)
    {
        auto fbsData = fbs::GetFlatData(buffer.data());
        data->resize(fbsData->data()->size());
        std::copy(
            fbsData->data()->begin(),
            fbsData->data()->end(),
            data->begin());
    }

} // namespace kiri_math
