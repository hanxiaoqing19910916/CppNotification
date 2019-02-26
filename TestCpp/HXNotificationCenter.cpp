//
//  HXNotificationCenter.cpp
//  TestCpp
//
//  Created by hanxiaoqing on 2019/2/19.
//  Copyright © 2019 sdk. All rights reserved.
//

#include "HXNotificationCenter.h"

namespace hx {
    
    NotificationCenter* NotificationCenter::m_center = nullptr;

    NotificationCenter* NotificationCenter::defaultCenter()  {
        if (m_center == nullptr) {
            m_center = new NotificationCenter();
        }
        return m_center;
    }
    NotificationCenter::NotificationCenter() {
    }
}

