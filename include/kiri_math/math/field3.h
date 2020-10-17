/*
 * @Author: Doyub Kim 
 * @Date: 2020-04-03 18:45:17 
 * @Last Modified by: Xu.Wang
 * @Last Modified time: 2020-04-18 20:30:01
 */

#ifndef _KIRI_MATH_FIELD3_H_
#define _KIRI_MATH_FIELD3_H_

#include <memory>

namespace kiri_math
{

    //! Abstract base class for 3-D fields.
    class Field3
    {
    public:
        Field3();

        virtual ~Field3();
    };

    typedef std::shared_ptr<Field3> Field3Ptr;

} // namespace kiri_math

#endif // _KIRI_MATH_FIELD3_H_
