#pragma once

namespace libpocoemulator
{

// Forward declaration.
class HttpsSession;
class HttpSession;

namespace types
{

//! Http session pointer type.
using HttpSessionPtr = Poco::SharedPtr<HttpSession>;
//! Https session pointer type.
using HttpsSessionPtr = Poco::SharedPtr<HttpsSession>;

} // namespace types
} // namespace libpocoemulator