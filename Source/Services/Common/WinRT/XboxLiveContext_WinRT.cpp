// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "pch.h"
#include "xsapi/services.h"
#include "../Common/xbox_live_context_impl.h"
#include "XboxLiveContext_WinRT.h"
#include "user_context.h"
#include "xbox_system_factory.h"
#if !(TV_API | XBOX_UWP)
#include "User_WinRT.h"
#endif
#include "xsapi/profile.h"
#include "xsapi/contextual_search_service.h"
#include "xsapi/xbox_live_app_config.h"
#if !TV_API
#include "notification_service.h"
#endif
#include "presence_internal.h"

using namespace Platform;
using namespace Windows::Foundation::Collections;

#if !XSAPI_CPP && !UNIT_TEST_SERVICES
bool g_is_xbox_live_creators_sdk = false;
#endif

NAMESPACE_MICROSOFT_XBOX_SERVICES_BEGIN

#if TV_API | XBOX_UWP
XboxLiveContext::XboxLiveContext(
    _In_ Windows::Xbox::System::User^ user
    ) 
{
    m_cppObj = std::make_shared<xbox::services::xbox_live_context>(user);
    
    Initialize();
}


Windows::Xbox::System::User^
XboxLiveContext::User::get()
{
    return m_cppObj->user();
}

#else
XboxLiveContext::XboxLiveContext(
    _In_ Microsoft::Xbox::Services::System::XboxLiveUser^ user
    ) 
{
    m_cppObj = std::make_shared<xbox::services::xbox_live_context>(user);

    Initialize();
}

Microsoft::Xbox::Services::System::XboxLiveUser^
XboxLiveContext::User::get()
{
    return m_cppObj->user();
}
#endif

void
XboxLiveContext::Initialize()
{
    m_xboxLiveContextSettings = ref new Microsoft::Xbox::Services::XboxLiveContextSettings(m_cppObj->settings());

    auto appConfig = xbox::services::xbox_live_app_config::get_app_config_singleton();

    m_appConfig = ref new Microsoft::Xbox::Services::XboxLiveAppConfiguration(appConfig);

    m_profileService = ref new Microsoft::Xbox::Services::Social::ProfileService(
        m_cppObj->profile_service()
        );

    m_achievementService = ref new Microsoft::Xbox::Services::Achievements::AchievementService(
        m_cppObj->achievement_service()
        );

    m_realTimeActivityService = ref new RealTimeActivity::RealTimeActivityService(
        m_cppObj->real_time_activity_service()
        );

    m_presenceService = ref new Presence::PresenceService(
        m_cppObj->presence_service()
        );

    m_titleStorageService = ref new TitleStorage::TitleStorageService(
        m_cppObj->title_storage_service()
        );

#if UWP_API
    m_eventsService = ref new Events::EventsService(
        m_cppObj->events_service()
        );
#endif

#if TV_API || UNIT_TEST_SERVICES
    m_catalogService = ref new Marketplace::CatalogService(
        m_cppObj->catalog_service()
        );

    m_inventoryService = ref new Marketplace::InventoryService(
        m_cppObj->inventory_service()
        );

    m_entertainmentProfileListService = ref new Microsoft::Xbox::Services::EntertainmentProfile::EntertainmentProfileListService(
        m_cppObj->entertainment_profile_list_service()
        );
#endif
}

Social::ProfileService^ 
XboxLiveContext::ProfileService::get()
{ 
    return m_profileService;
}

Achievements::AchievementService^
XboxLiveContext::AchievementService::get()
{
    return m_achievementService;
}

RealTimeActivity::RealTimeActivityService^
XboxLiveContext::RealTimeActivityService::get()
{
    return m_realTimeActivityService;
}

Presence::PresenceService^
XboxLiveContext::PresenceService::get()
{
    return m_presenceService;
}

TitleStorage::TitleStorageService^
XboxLiveContext::TitleStorageService::get()
{
    return m_titleStorageService;
}

#if UWP_API
Events::EventsService^
XboxLiveContext::EventsService::get()
{
    return m_eventsService;
}
#endif

#if TV_API || UNIT_TEST_SERVICES
Marketplace::CatalogService^
XboxLiveContext::CatalogService::get()
{
    return m_catalogService;
}

Marketplace::InventoryService^
XboxLiveContext::InventoryService::get()
{
    return m_inventoryService;
}

EntertainmentProfile::EntertainmentProfileListService^
XboxLiveContext::EntertainmentProfileListService::get()
{
    return m_entertainmentProfileListService;
}
#endif

Microsoft::Xbox::Services::XboxLiveContextSettings^
XboxLiveContext::Settings::get()
{ 
    return m_xboxLiveContextSettings;
}

Microsoft::Xbox::Services::XboxLiveAppConfiguration^
XboxLiveContext::AppConfig::get()
{ 
    return m_appConfig;
}

std::shared_ptr<xbox::services::xbox_live_context>
XboxLiveContext::GetCppObj() const
{
    return m_cppObj;
}

NAMESPACE_MICROSOFT_XBOX_SERVICES_END