import { AsyncStorage } from 'react-native'
import { SERVER_LOCATION } from 'react-native-dotenv'
import { ApolloClient } from 'apollo-client'
import { createHttpLink } from 'apollo-link-http'
import { setContext } from 'apollo-link-context'
import {
  InMemoryCache,
  IntrospectionFragmentMatcher,
} from 'apollo-cache-inmemory'

let token = null
const getToken = () => {
  return AsyncStorage.getItem('USER_TOKEN')
}

const fragmentMatcher = new IntrospectionFragmentMatcher({
  introspectionQueryResultData: {
    __schema: {
      types: [
        {
          kind: 'UNION',
          name: 'TransactionOriginUnion',
          possibleTypes: [
            { name: 'TransactionAccount' },
            { name: 'TransactionBond' },
            { name: 'TransactionCreditCard' },
          ],
        },
      ],
    },
  },
})

const httpLink = createHttpLink({
  uri: SERVER_LOCATION,
})

console.log('Connecting to ', SERVER_LOCATION)

const authLink = setContext((_, { headers }) => {
  // return the headers to the context so httpLink can read them
  return getToken().then(token => ({
    headers: {
      ...headers,
      authorization: token,
    },
  }))
})

const client = new ApolloClient({
  link: authLink.concat(httpLink),
  cache: new InMemoryCache({
    fragmentMatcher,
  }),
  connectToDevTools: process.env.NODE_ENV === 'development',
})

export default client
