#ifndef MODEL_CONSTANTS_H_
#define MODEL_CONSTANTS_H_

#include <QString>

namespace constants {
const double kEpsilon = 0.0001;

const int kGameWidth = 1920;
const int kGameHeight = 1080;

const int kTimeBetweenTicks = 17;
const int kTimeScale = 100;

// Coefficient describes, how small SemiMinorAxe in compare between SemiMajorAxe
const double kSemiMinorCoefficient = 0.8;
const double kRefundCoefficient = 0.8;

const double kFontSize = 32;
const QString kCurrency = "$";

const int kApplicationRestartCode = 123456;

const QString kCompanyName = "Giggling Penguin";
const QString kApplicationName = "Tech vs Cats";
}  // namespace constants

#endif  // MODEL_CONSTANTS_H_
