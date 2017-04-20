﻿// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once
#if !TV_API
#include "User_WinRT.h"
#endif
#include "ProfileService_WinRT.h"
#include "ReputationService_WinRT.h"
#include "AppConfiguration_WinRT.h"
#include "Achievementservice_WinRT.h"
#include "XboxLiveContextSettings_WinRT.h"
#include "RealTimeActivityService_WinRT.h"
#include "PresenceService_WinRT.h"
#include "TitleStorageService_WinRT.h"
#include "EventsService_WinRT.h"
#if TV_API || UNIT_TEST_SERVICES
#include "CatalogService_WinRT.h"
#include "InventoryService_WinRT.h"
#include "EntertainmentProfileListService_WinRT.h"
#endif
#include "local_config.h"

namespace xbox { namespace services { class xbox_live_context; } }

NAMESPACE_MICROSOFT_XBOX_SERVICES_BEGIN

/// <summary>
/// Defines methods used to retrieve objects that in turn provide access to different Xbox Live service components.
/// 
/// Note: the XboxLiveContext is unique per instance. Changing state on one instance for a user does not affect a second instance of the context for the same user. Using multiple instances can therefore result in unexpected behavior. Titles should ensure to only use one instance of the XboxLiveContext per user.
/// </summary> 
public ref class XboxLiveContext sealed
{
public:

#if TV_API | XBOX_UWP
    XboxLiveContext(_In_ Windows::Xbox::System::User^ user);

    /// <summary>
    /// Returns the associated system user.
    /// </summary>
    property Windows::Xbox::System::User^ User { Windows::Xbox::System::User^ get(); }

#else
    XboxLiveContext(_In_ Microsoft::Xbox::Services::System::XboxLiveUser^ user);

    /// <summary>
    /// Returns the associated system user. 
    /// </summary>
    property Microsoft::Xbox::Services::System::XboxLiveUser^ User { Microsoft::Xbox::Services::System::XboxLiveUser^ get(); }

#endif

    /// <summary>
    /// Returns object containing access methods to the Xbox Profile service.
    /// </summary>
    property Social::ProfileService^ ProfileService { Social::ProfileService^ get(); }

    /// <summary>
    /// Returns object containing access methods to the Xbox Reputation service.
    /// </summary>
    property Social::ReputationService^ ReputationService { Social::ReputationService^ get(); }

    /// <summary>
    /// Returns object containing access methods to the Xbox Achievement service.
    /// </summary>
    property Achievements::AchievementService^ AchievementService { Achievements::AchievementService^ get(); }

    /// <summary>
    /// Returns object containing access methods to the Xbox Real Time Activity service.
    /// </summary>
    property RealTimeActivity::RealTimeActivityService^ RealTimeActivityService { RealTimeActivity::RealTimeActivityService^ get(); }

    /// <summary>
    /// Returns object containing access methods to the Presence service.
    /// </summary>
    property Presence::PresenceService^ PresenceService { Presence::PresenceService^ get(); }

    /// <summary>
    /// Returns object containing access methods to the TitleStorage service.
    /// </summary>
    property TitleStorage::TitleStorageService^ TitleStorageService{ TitleStorage::TitleStorageService^ get(); }

#if UWP_API
    /// <summary>
    /// Returns object containing access methods to the events service.
    /// </summary>
    property Events::EventsService^ EventsService { Events::EventsService^ get(); }
#endif

#if TV_API || UNIT_TEST_SERVICES
    /// <summary>
    /// Returns object containing access methods to the Catalog service.
    /// </summary>
    property Marketplace::CatalogService^ CatalogService { Marketplace::CatalogService^ get(); }

    /// <summary>
    /// Returns object containing access methods to the Inventory service.
    /// </summary>
    property Marketplace::InventoryService^ InventoryService { Marketplace::InventoryService^ get(); }
    
    /// <summary>
    /// Returns object containing access methods to the Xbox String service.
    /// </summary>
    property EntertainmentProfile::EntertainmentProfileListService^ EntertainmentProfileListService { EntertainmentProfile::EntertainmentProfileListService^ get(); }
#endif // #if TV_API || UNIT_TEST_SERVICES

    /// <summary>
    /// Returns an object containing settings that apply to all REST calls made such as retry and diagnostic settings.
    /// </summary>
    property Microsoft::Xbox::Services::XboxLiveContextSettings^ Settings { Microsoft::Xbox::Services::XboxLiveContextSettings^ get(); }

    /// <summary>
    /// Returns an object containing Xbox Live app config such as title ID
    /// </summary>
    property Microsoft::Xbox::Services::XboxLiveAppConfiguration^ AppConfig { Microsoft::Xbox::Services::XboxLiveAppConfiguration^ get(); }

internal:
    std::shared_ptr<xbox::services::xbox_live_context> GetCppObj() const;

private:
    void Initialize();

    std::shared_ptr<xbox::services::xbox_live_context> m_cppObj;
    Microsoft::Xbox::Services::XboxLiveContextSettings^ m_xboxLiveContextSettings;
    Microsoft::Xbox::Services::XboxLiveAppConfiguration^ m_appConfig;
    Social::ProfileService^ m_profileService;
    Social::ReputationService^ m_reputationService;
    Achievements::AchievementService^ m_achievementService;
    RealTimeActivity::RealTimeActivityService^ m_realTimeActivityService;
    Presence::PresenceService^ m_presenceService;
    TitleStorage::TitleStorageService^ m_titleStorageService;
#if UWP_API
    Events::EventsService^ m_eventsService;
#endif
#if TV_API || UNIT_TEST_SERVICES
    Marketplace::CatalogService^ m_catalogService;
    Marketplace::InventoryService^ m_inventoryService;
    EntertainmentProfile::EntertainmentProfileListService^ m_entertainmentProfileListService;
#endif

    function_context m_signInContext;
    function_context m_signOutContext;
};

NAMESPACE_MICROSOFT_XBOX_SERVICES_END
