/**
* This file has been modified from its orginal sources.
*
* Copyright (c) 2012 Software in the Public Interest Inc (SPI)
* Copyright (c) 2012 David Pratt
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
***
* Copyright (c) 2008-2012 Appcelerator Inc.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
**/

#include "http_server_response.h"
#include <Poco/Net/HTTPCookie.h>
#include <curl/curl.h>
#include "../../common.h"

namespace ti
{
    HttpServerResponse::HttpServerResponse(Poco::Net::HTTPServerResponse &response) :
        StaticBoundObject("Network.HTTPServerResponse"),
        response(response)
    {
        /**
         * @tiapi(method=True,name=Network.HTTPServerResponse.setStatus,since=0.3) set the status of this response
         * @tiarg(for=Network.HTTPServerResponse.setStatus,type=String,name=status) the status, i.e "200"
         */
        SetMethod("setStatus",&HttpServerResponse::SetStatus);
        
        /**
         * @tiapi(method=True,name=Network.HTTPServerResponse.setReason,since=0.3) set the reason of this response
         * @tiarg(for=Network.HTTPServerResponse.setReason,type=String,name=reason) the reason, i.e "OK"
         */
        SetMethod("setReason",&HttpServerResponse::SetReason);
        
        /**
         * @tiapi(method=True,name=Network.HTTPServerResponse.setStatusAndReason,since=0.3) set the status and reason of this response
         * @tiarg(for=Network.HTTPServerResponse.setStatusAndReason,type=String,name=status) the status, i.e "200"
         * @tiarg(for=Network.HTTPServerResponse.setStatusAndReason,type=String,name=reason) the reason, i.e "OK"
         */
        SetMethod("setStatusAndReason",&HttpServerResponse::SetStatusAndReason);
        
        /**
         * @tiapi(method=True,name=Network.HTTPServerResponse.setContentType,since=0.3) set the content type of this response
         * @tiarg(for=Network.HTTPServerResponse.setContentType,type=String,name=type) the content type, i.e "text/plain"
         */
        SetMethod("setContentType",&HttpServerResponse::SetContentType);
        
        /**
         * @tiapi(method=True,name=Network.HTTPServerResponse.setContentLength,since=0.3) set the content length of this response
         * @tiarg(for=Network.HTTPServerResponse.setContentLength,type=Number,name=length) the content length, i.e 100
         */
        SetMethod("setContentLength",&HttpServerResponse::SetContentLength);
        
        /**
         * @tiapi(method=True,name=Network.HTTPServerResponse.addCookie,since=0.3) add a cookie to this response
         * @tiarg(for=Network.HTTPServerResponse.addCookie,type=String,name=name) the cookie name
         * @tiarg(for=Network.HTTPServerResponse.addCookie,type=String,name=value) the cookie value
         * @tiarg(for=Network.HTTPServerResponse.addCookie,type=Number,name=maxAge,optional=True) the cookie's maximum age
         * @tiarg(for=Network.HTTPServerResponse.addCookie,type=String,name=domain,optional=True) the cookie's domain
         * @tiarg(for=Network.HTTPServerResponse.addCookie,type=String,name=path,optional=True) the cookie's path
         */
        SetMethod("addCookie",&HttpServerResponse::AddCookie);
        
        /**
         * @tiapi(method=True,name=Network.HTTPServerResponse.setHeader,since=0.3) set an HTTP header of this response
         * @tiarg(for=Network.HTTPServerResponse.setHeader,type=String,name=name) the header name
         * @tiarg(for=Network.HTTPServerResponse.setHeader,type=String,name=value) the header value
         */
        SetMethod("setHeader",&HttpServerResponse::SetHeader);
        
        /**
         * @tiapi(method=True,name=Network.HTTPServerResponse.write,since=0.3) write content into this response
         * @tiarg(for=Network.HTTPServerResponse.write,type=String,name=data) content to write (can be string or bytes content)
         */
        SetMethod("write",&HttpServerResponse::Write);
    }
    HttpServerResponse::~HttpServerResponse()
    {
    }
    void HttpServerResponse::SetStatus(const ValueList& args, ValueRef result)
    {
        std::string status = args.at(0)->ToString();
        response.setStatus(status);
    }
    void HttpServerResponse::SetReason(const ValueList& args, ValueRef result)
    {
        std::string reason = args.at(0)->ToString();
        response.setReason(reason);
    }
    void HttpServerResponse::SetStatusAndReason(const ValueList& args, ValueRef result)
    {
        std::string status = args.at(0)->ToString();
        std::string reason = args.at(1)->ToString();
        response.setStatus(status);
        response.setReason(reason);
    }
    void HttpServerResponse::SetContentType(const ValueList& args, ValueRef result)
    {
        std::string ct = args.at(0)->ToString();
        response.setContentType(ct);
    }
    void HttpServerResponse::SetContentLength(const ValueList& args, ValueRef result)
    {
        int len = args.at(0)->ToInt();
        response.setContentLength(len);
    }
    void HttpServerResponse::AddCookie(const ValueList& args, ValueRef result)
    {
        //name,value,[max_age,domain,path]
        std::string name = args.at(0)->ToString();
        std::string value = args.at(1)->ToString();
        Poco::Net::HTTPCookie cookie(name,value);
        if (args.size()>2)
        {
            int max_age = args.at(2)->ToInt();
            cookie.setMaxAge(max_age);
        }
        if (args.size()>3)
        {
            std::string domain = args.at(3)->ToString();
            cookie.setDomain(domain);
        }
        if (args.size()>4)
        {
            std::string path = args.at(4)->ToString();
            cookie.setPath(path);
        }
    }
    void HttpServerResponse::SetHeader(const ValueList& args, ValueRef result)
    {
        std::string name = args.at(0)->ToString();
        std::string value = args.at(1)->ToString();
        response.set(name,value);
    }
    void HttpServerResponse::Write(const ValueList& args, ValueRef result)
    {
        std::ostream& ostr = response.send();
        
        if (args.at(0)->IsString())
        {
            ostr << args.at(0)->ToString();
            ostr.flush();
            return;
        }
        else if (args.at(0)->IsObject())
        {
            BytesRef bytes(ObjectToBytes(args.at(0)->ToObject()));
            if (bytes.isNull())
                throw ValueException::FromString("Don't know how to write that kind of data.");

            ostr.write(bytes->Pointer(), bytes->Length());
        }
        else
        {
            throw ValueException::FromString("Don't know how to write that kind of data.");
        }
    }
}
