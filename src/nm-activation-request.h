/* NetworkManager -- Network link manager
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * (C) Copyright 2005 Red Hat, Inc.
 */

#ifndef NM_ACTIVATION_REQUEST_H
#define NM_ACTIVATION_REQUEST_H

#include <glib/gtypes.h>
#include <glib-object.h>
#include "nm-connection.h"

#define NM_TYPE_ACT_REQUEST            (nm_act_request_get_type ())
#define NM_ACT_REQUEST(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), NM_TYPE_ACT_REQUEST, NMActRequest))
#define NM_ACT_REQUEST_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), NM_TYPE_ACT_REQUEST, NMActRequestClass))
#define NM_IS_ACT_REQUEST(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), NM_TYPE_ACT_REQUEST))
#define NM_IS_ACT_REQUEST_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((obj), NM_TYPE_ACT_REQUEST))
#define NM_ACT_REQUEST_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), NM_TYPE_ACT_REQUEST, NMActRequestClass))

typedef struct {
	GObject parent;
} NMActRequest;

typedef struct {
	GObjectClass parent;

	/* Signals */
	void (*connection_secrets_updated)  (NMActRequest *req,
	                                     NMConnection *connection,
	                                     const char * setting);
	void (*deferred_activation_timeout) (NMActRequest *req);
	void (*deferred_activation_start)   (NMActRequest *req);
} NMActRequestClass;

GType nm_act_request_get_type (void);

NMActRequest *nm_act_request_new          (NMConnection *connection,
                                           const char *specific_object,
                                           gboolean user_requested);

NMActRequest *nm_act_request_new_deferred (const char *service_name,
                                           const char *connection_path,
                                           const char *specific_object,
                                           gboolean user_requested);

NMConnection *nm_act_request_get_connection     (NMActRequest *req);
const char *  nm_act_request_get_specific_object(NMActRequest *req);
gboolean      nm_act_request_get_user_requested (NMActRequest *req);

#endif /* NM_ACTIVATION_REQUEST_H */
