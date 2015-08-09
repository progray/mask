set(MASK_BASE_SRCS
    base/Query.cc
    base/Request.cc
    base/Response.cc
    base/StringUtil.cc
    )

set(MASK_HTTP_SRCS
    http/HttpContext.cc
    http/HttpRequest.cc
    http/HttpResponse.cc
    http/HttpServer.cc
    )

set(MASK_APP_SRCS
    app/app.cc
    )

add_library(mask ${MASK_BASE_SRCS} ${MASK_HTTP_SRCS}
		 ${MASK_APP_SRCS})
target_link_libraries(mask ${HTTP_PARSER_LIBRARIES}
			   ${MUDUO_NET_LIBRARIES})

add_subdirectory(base/tests)
add_subdirectory(http/tests)
