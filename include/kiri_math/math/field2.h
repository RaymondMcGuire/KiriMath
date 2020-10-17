

#ifndef _KIRI_MATH_FIELD2_H_
#define _KIRI_MATH_FIELD2_H_

#include <memory>

namespace kiri_math
{

    //! Abstract base class for 2-D fields.
    class Field2
    {
    public:
        Field2();

        virtual ~Field2();
    };

    typedef std::shared_ptr<Field2> Field2Ptr;

} // namespace kiri_math

#endif // _KIRI_MATH_FIELD2_H_
