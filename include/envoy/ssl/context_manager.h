#pragma once

#include <functional>

#include "envoy/secret/secret_manager.h"
#include "envoy/ssl/context.h"
#include "envoy/ssl/context_config.h"
#include "envoy/stats/stats.h"

namespace Envoy {
namespace Ssl {

/**
 * Manages all of the SSL contexts in the process
 */
class ContextManager {
public:
  virtual ~ContextManager() {}

  /**
   * Builds a ClientContext from a ClientContextConfig.
   */
  virtual ClientContextSharedPtr createSslClientContext(Stats::Scope& scope,
                                                        const ClientContextConfig& config) PURE;

  /**
   * Updates ClientContext and returns updated ClientContext.
   *
   * @param context ClientContext to be updated.
   * @param scope stats scope.
   * @param config supplies the configuration for ClientContext.
   * @return an updated ClientContext.
   */
  virtual ClientContextSharedPtr updateSslClientContext(const ClientContextSharedPtr context,
                                                        Stats::Scope& scope,
                                                        const ClientContextConfig& config) PURE;

  /**
   * Builds a ServerContext from a ServerContextConfig.
   */
  virtual ServerContextSharedPtr
  createSslServerContext(Stats::Scope& scope, const ServerContextConfig& config,
                         const std::vector<std::string>& server_names) PURE;

  /**
   * Updates ServerContext and returns updated ServerContext.
   *
   * @param context ServerContext to be updated.
   * @param scope stats scope
   * @param config supplies the configuration for ServerContext.
   * @param server_names server names.
   * @return an updated ServerContext.
   */
  virtual ServerContextSharedPtr
  updateSslServerContext(const ServerContextSharedPtr context, Stats::Scope& scope,
                         const ServerContextConfig& config,
                         const std::vector<std::string>& server_names) PURE;

  /**
   * @return the number of days until the next certificate being managed will expire.
   */
  virtual size_t daysUntilFirstCertExpires() const PURE;

  /**
   * Iterate through all currently allocated contexts.
   */
  virtual void iterateContexts(std::function<void(const Context&)> callback) PURE;

  /**
   * release context from this manager.
   */
  virtual void releaseContext(Context* context) PURE;

  /**
   * @return a SecretManager.
   */
  virtual Secret::SecretManager& secretManager() PURE;
};

} // namespace Ssl
} // namespace Envoy
