package main

import (
	"context"
	"net/http"

	"github.com/google/uuid"
)

type contextKey string

const tenantIDKey contextKey = "tenant_id"

// TODO A2: generate UUID per request, set response header X-Request-ID
func requestIDMiddleware(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		requestId:=r.Header.Get("X-Request-ID")
		if(requestId==""){
			requestId=uuid.New().String()
		}
		w.Header().Set("X-Request-ID",requestId)
		next.ServeHTTP(w, r)
	})
}

// TODO A2: read X-API-Key header; if missing/invalid → 401; else set tenant_id in context
func tenantAuthMiddleware(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		next.ServeHTTP(w, r)
	})
}

func tenantFromContext(ctx context.Context) string {
	// TODO: read tenant_id from context after middleware sets it
	return ""
}
