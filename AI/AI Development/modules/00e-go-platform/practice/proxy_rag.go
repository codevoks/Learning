package main

import (
	"net/http"
	"os"
)

// Python RAG service URL — docker-compose mein rag:8001
func ragBaseURL() string {
	if u := os.Getenv("RAG_SERVICE_URL"); u != "" {
		return u
	}
	return "http://localhost:8001"
}

// TODO A3: read request body, forward POST to ragBaseURL()+"/internal/query"
// Set header X-Tenant-ID from context
// Return upstream status + body to client
func proxyToRAG(w http.ResponseWriter, r *http.Request) {
	http.Error(w, "not implemented", http.StatusNotImplemented)
}
