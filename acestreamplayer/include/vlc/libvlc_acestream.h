#ifndef VLC_libvlc_ACESTREAM_H
#define VLC_libvlc_ACESTREAM_H 1

# ifdef __cplusplus
extern "C" {
# else
#  include <stdbool.h>
# endif

/** \defgroup libvlc_acestream_object_t AceStream Object
 * @{
 */
 
typedef struct libvlc_acestream_object_t libvlc_acestream_object_t;

/**
 * Description of url type of acestream file
 */
typedef enum libvlc_acestream_id_type_t
{
    libvlc_ace_id_type_Unsupport = -1,  // not acestream
    libvlc_ace_id_type_TorrentUrl = 0,  // simple url for torrent/acelive file (http://, file:///)
    libvlc_ace_id_type_DirectUrl,       // direct url for media file (for js extension)
    libvlc_ace_id_type_Infohash,        // infohash of acestream file
    libvlc_ace_id_type_Player,          // player content id
    libvlc_ace_id_type_Raw,             // raw acestream file data
    libvlc_ace_id_type_Efile            // efile
} libvlc_acestream_id_type_t;

/**
 * Description of load commande type
 */
typedef enum libvlc_acestream_load_type_t
{
    libvlc_ace_load_Async = true,   // asynchronous load command (recommendet to use)
    libvlc_ace_load_Sync = false    // sync load command
} libvlc_acestream_load_type_t;

/**
 * Description of acestream engine state ( for libvlc_AcestreamState event )
 */
typedef enum libvlc_acestream_state_t {
    libvlc_ace_state_Notlaunched = -1,
    libvlc_ace_state_Idle = 0,
    libvlc_ace_state_Prebuffering,
    libvlc_ace_state_Downloading,
    libvlc_ace_state_Buffering,
    libvlc_ace_state_Completed,
    libvlc_ace_state_HashChecking,
    libvlc_ace_state_Error,
    libvlc_ace_state_Connecting,
    libvlc_ace_state_Loading,
    libvlc_ace_state_Launching
} libvlc_acestream_state_t;

/**
 * Description for url type ( for libvlc_AcestreamShowUrl event ) DEPRECATED
 */
typedef enum libvlc_acestream_showurl_type_t {
    libvlc_ace_showurl_Undf = -1,
    libvlc_ace_showurl_Ad,
    libvlc_ace_showurl_Notification,
    libvlc_ace_showurl_Services,
    libvlc_ace_showurl_Overlay,
    libvlc_ace_showurl_StopAd
} libvlc_acestream_showurl_type_t;

/**
 * Create an libvlc_acestream_object instance
 *
 * \param p_instance libvlc instance
 * \return libvlc_acestream_object instance, or NULL on error
 */
LIBVLC_API libvlc_acestream_object_t *libvlc_acestream_object_new( libvlc_instance_t *p_instance );

/**
 * Release libvlc_acestream_object created with libvlc_acestream_object_new().
 *
 * \param p_ace a libvlc_acestream_object created with libvlc_acestream_object_new()
 */
LIBVLC_API void libvlc_acestream_object_release( libvlc_acestream_object_t *p_ace );

/**
 * Retain reference to a libvlc_acestream_object
 *
 * \param p_ace a libvlc_acestream_object created with libvlc_acestream_object_new()
 */
LIBVLC_API void libvlc_acestream_object_retain( libvlc_acestream_object_t *p_ace );

/**
 * Get libvlc_event_manager from this libvlc_acestream_object instance.
 * The p_event_manager is immutable, so you don't have to hold the lock
 *
 * \param p_ace a libvlc_acestream_object instance
 * \return libvlc_event_manager
 */
LIBVLC_API libvlc_event_manager_t *libvlc_acestream_object_event_manager( libvlc_acestream_object_t *p_ace );

/**
 * Set the libvlc_media_list_player associated with the libvlc_acestream_object
 *
 * \param p_ace a libvlc_acestream_object instance
 * \param p_mlist_player a libvlc_media_list_player instance
 */
LIBVLC_API void libvlc_acestream_object_set_media_list_player( libvlc_acestream_object_t *p_ace, 
                                                               libvlc_media_list_player_t *p_mlist_player );

/**
 * Command for engine to load acestream file or content
 *
 * \param p_ace a libvlc_acestream_object instance
 * \param psz_id url to file or content
 * \param psz_name name of file or content or NULL
 * \param type libvlc_acestream_id_type_t value depends on psz_id (psz_id = "http://..., file:///..., etc" - type = libvlc_ace_id_type_TorrentUrl,
 *          contentid: for example "184c812931a9f881e8e7104aa3808b08b7840815" - type = libvlc_ace_id_type_Player)
 * \param load_type libvlc_acestream_load_type_t (libvlc_ace_load_Async recommendet)
 * \param option_string vlc options for example ":deinterlace=1 :deinterlace-mode=linear" or NULL
 * \param developer id of developer
 * \param affiliate id of affiliate
 * \param zone id of zone
 */
LIBVLC_API int libvlc_acestream_object_load( libvlc_acestream_object_t *p_ace, 
                                             const char *psz_id, 
                                             const char *psz_name, 
                                             libvlc_acestream_id_type_t type,
                                             libvlc_acestream_load_type_t load_type, 
                                             const char *option_string, 
                                             int developer, 
                                             int affiliate, 
                                             int zone );

/**
 * Deprecated
 */
LIBVLC_API bool libvlc_acestream_object_start( libvlc_acestream_object_t *p_ace, 
                                               const char *psz_id, 
                                               const char *psz_indexes, 
                                               libvlc_acestream_id_type_t type,
                                               int quality, 
                                               int developer, 
                                               int affiliate, 
                                               int zone, 
                                               int start_position );

/**
 * Command for engine to stop
 *
 * \param p_ace a libvlc_acestream_object instance
 * \return success
 */
LIBVLC_API bool libvlc_acestream_object_stop( libvlc_acestream_object_t *p_ace );

/**
 * Get content id of acestream media (Deprecated)
 *
 * \param p_ace a libvlc_acestream_object instance
 * \param infohash infohash value
 * \param checksum checksum value
 * \param developer id of developer
 * \param affiliate id of affiliate
 * \param zone id of zone
 * \param result pointer to allocated mamory for writing result (memory must be allocated and free by caller)
 * \return same as result
 */
LIBVLC_API char *libvlc_acestream_object_get_content_id( libvlc_acestream_object_t *p_ace, 
                                                         const char *infohash, 
                                                         const char *checksum, 
                                                         int developer, 
                                                         int affiliate, 
                                                         int zone, 
                                                         char *result );

/**
 * Get content id of acestream media
 *
 * \param p_ace a libvlc_acestream_object instance
 * \param index of acestream media in media list
 * \param result pointer to allocated mamory for writing result (memory must be allocated and free by caller)
 * \return same as result
 */
LIBVLC_API char *libvlc_acestream_object_get_content_id_by_index( libvlc_acestream_object_t *p_ace, 
                                                                  int index, 
                                                                  char *result );

/**
 * Command for engine to save acestream media
 *
 * \param p_ace a libvlc_acestream_object instance
 * \param infohash infohash value of acestream media (libvlc_media_get_acestream_infohash)
 * \param item_index acestream item index (libvlc_media_get_acestream_index)
 * \param pathtofile path where file will be saved
 * \return success
 */
LIBVLC_API bool libvlc_acestream_object_save( libvlc_acestream_object_t *p_ace, 
                                              const char *infohash, 
                                              int item_index, 
                                              const char *pathtofile );

/**
 * Command for engine to seek live broadcast
 *
 * \param p_ace a libvlc_acestream_object instance
 * \param position position to seek (calculated from libvlc_MediaPlayerLivePosChanged event description data)
 * \return success
 */
LIBVLC_API bool libvlc_acestream_object_live_seek( libvlc_acestream_object_t *p_ace, int position );

/**
 * Command for engine to save user data after libvlc_AcestreamShowUserDataDialog event
 *
 * \param p_ace a libvlc_acestream_object instance
 * \param gender 
 * \param age
 * \return success
 */
LIBVLC_API bool libvlc_acestream_object_user_data( libvlc_acestream_object_t *p_ace, int gender, int age );

/**
 * Get engine version ( for js extensions )
 *
 * \param p_ace a libvlc_acestream_object instance
 * \param result pointer to allocated mamory for writing result (memory must be allocated and free by caller)
 * \return same as result
 */
LIBVLC_API char *libvlc_acestream_object_get_engine_version( libvlc_acestream_object_t *p_ace, char *result );

/**
 * Method must be called on mouse clisk on video window
 *
 * \param p_ace a libvlc_acestream_object instance
 * \param activate true if single click, false if double click
 */
LIBVLC_API void libvlc_acestream_object_activate_video_click( libvlc_acestream_object_t *p_ace, bool activate );

/**
 * Command for engine to skip advertisement 
 *  Call it only if libvlc_AcestreamAdParams event description data "skippoffset" reached
 *  
 * \param p_ace a libvlc_acestream_object instance
 */
LIBVLC_API void libvlc_acestream_object_skip( libvlc_acestream_object_t *p_ace );

/**
 * Reports engine that pause context advertisement shown
 *  
 * \param p_ace a libvlc_acestream_object instance
 * \param id advertisement id
 */
LIBVLC_API void libvlc_acestream_object_register_ad_shown( libvlc_acestream_object_t *p_ace, const char *id );

/**
 * Request for next pause context advertisement to preload
 *  
 * \param p_ace a libvlc_acestream_object instance
 */
LIBVLC_API void libvlc_acestream_object_request_pause_ad( libvlc_acestream_object_t *p_ace);

/**
 * Reports engine that context advertisement closed by user
 *  
 * \param p_ace a libvlc_acestream_object instance
 * \param id advertisement id
 */
LIBVLC_API void libvlc_acestream_object_register_ad_closed( libvlc_acestream_object_t *p_ace, const char *id );

/**
 * Return volume value for advertisement
 *  
 * \param p_ace a libvlc_acestream_object instance
 * \return volume value
 */
LIBVLC_API int libvlc_acestream_object_get_ad_volume( libvlc_acestream_object_t *p_ace );

/** @} acestream */

# ifdef __cplusplus
}
# endif
    
#endif