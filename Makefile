
.PHONY: help
help:   ## Show this help
	@awk 'BEGIN {FS = ":.*##"; printf "Usage: make \033[36;1m[target]\033[0m\n"} /^[a-zA-Z0-9_-]+:.*?##/ { printf "  \033[36;1m%-10s\033[0m %s\n", $$1, $$2 } /^##@/ { printf "\n\033[1m%s\033[0m\n", substr($$0, 5) } ' $(MAKEFILE_LIST)


.PHONY: flash
flash: ## flash d1 mini
	pio run -t upload -e d1_mini

.PHONY: test
test: ## run native tests
	pio test -e native -v
