#include <httpd.h>
#include <http_core.h>
#include <http_protocol.h>

// https://ci.apache.org/projects/httpd/trunk/doxygen/structrequest__rec.html#afecc56ea8fb015aa52477dba471a6612
// https://stackoverflow.com/questions/36892699/set-custom-header-to-apache-response-within-a-module

static int hello_handler(request_rec *r) {
    /* First off, we need to check if this is a call for the "example-handler" handler.
     * If it is, we accept it and do our things, if not, we simply return DECLINED,
     * and the server will try somewhere else.
     */
    if (!r->handler || strcmp(r->handler, "hello_handler")) return (DECLINED);

    /* Now that we are handling this request, we'll write out "Hello, world!" to the client.
     * To do so, we must first set the appropriate content type, followed by our output.
     */
    // ap_set_content_type(r, "text/html");
    r->status = 401;
    apr_table_setn(r->headers_out, "Pippo", "pluto");
    ap_rprintf(r, "Hello, world!");

    /* Lastly, we must tell the server that we took care of this request and everything went fine.
     * We do so by simply returning the value OK to the server.
     */

    return OK; //OK;
}

static void register_hooks(apr_pool_t *pool) {
    /* Create a hook in the request handler, so we get called when a request arrives */
    ap_hook_handler(hello_handler, NULL, NULL, APR_HOOK_LAST);
}

module AP_MODULE_DECLARE_DATA hello_module = {
    STANDARD20_MODULE_STUFF,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    register_hooks   /* Our hook registering function */
};
