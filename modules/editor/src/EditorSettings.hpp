/*
    Copyright 2020 VUKOZ

    This file is part of 3D Forest.

    3D Forest is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    3D Forest is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with 3D Forest.  If not, see <https://www.gnu.org/licenses/>.
*/

/** @file EditorSettings.hpp */

#ifndef EDITOR_SETTINGS_HPP
#define EDITOR_SETTINGS_HPP

#include <Vector3.hpp>
#include <string>
#include <vector>

/** Editor Settings. */
class EditorSettings
{
public:
    /** Editor Settings View. */
    class View
    {
    public:
        enum ColorSource
        {
            COLOR_SOURCE_COLOR,
            COLOR_SOURCE_INTENSITY,
            COLOR_SOURCE_RETURN_NUMBER,
            COLOR_SOURCE_NUMBER_OF_RETURNS,
            COLOR_SOURCE_CLASSIFICATION
        };

        View();

        float pointSize() const;
        void setPointSize(float size);

        bool isFogEnabled() const;
        void setFogEnabled(bool b);

        void setPointColor(float r, float g, float b);
        const Vector3<float> &pointColor() const { return pointColor_; }
        float pointColorRed() const { return pointColor_[0]; }
        float pointColorGreen() const { return pointColor_[1]; }
        float pointColorBlue() const { return pointColor_[2]; }

        const Vector3<float> &background() const { return background_; }

        size_t colorSourceSize() const;
        const char *colorSourceString(size_t id) const;
        bool isColorSourceEnabled(size_t id) const;
        void setColorSourceEnabled(size_t id, bool v);

        void read(const Json &in);
        Json &write(Json &out) const;

    protected:
        float pointSize_;
        bool fogEnabled_;
        Vector3<float> pointColor_;
        Vector3<float> background_;
        std::vector<std::string> colorSourceString_;
        std::vector<bool> colorSourceEnabled_;
    };

    const View &view() const { return view_; }
    void setView(const View &view);

    void read(const Json &in);
    Json &write(Json &out) const;

protected:
    View view_;
};

#endif /* EDITOR_SETTINGS_HPP */
