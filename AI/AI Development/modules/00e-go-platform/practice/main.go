package main

import (
	"log"
	"net/http"

	"github.com/go-chi/chi/v5"
)

func main() {
	r := chi.NewRouter()

	// TODO A2: r.Use(requestIDMiddleware)
	r.Use(requestIDMiddleware)
	// TODO A2: r.Use(tenantAuthMiddleware)

	// TODO A1: GET /health → {"ok":true}
	r.Get("/health", func(w http.ResponseWriter, r *http.Request) {
		// http.Error(w, "not implemented", http.StatusNotImplemented)
		w.Write([]byte(`{"ok":true}`))
	})

	// TODO A3: POST /v1/query → proxyToRAG(w, r)
	r.Post("/v1/query", func(w http.ResponseWriter, r *http.Request) {
		http.Error(w, "not implemented", http.StatusNotImplemented)
	})

	log.Println("listening :8080")
	log.Fatal(http.ListenAndServe(":8080", r))
}
